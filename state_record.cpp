
#ifdef DEBUG
#include <iostream>
#endif

#include "state_record.h"

using namespace std;

void
StateRecord::clear()
{
    state_set.clear();
}

bool
StateRecord::check_and_insert( KamiState const &state)
{
    ColorMap map;
    for ( auto const &group_kv : state.groups) {
        GID gid = group_kv.first;
        Group const &group = group_kv.second;

        auto map_it = map.find( group.color);
        if ( map_it == map.end()) {
            auto result = map.emplace( group.color, GroupSet());
            map_it = result.first;
        }
        map_it->second.insert( gid);
    }

    AbstractState abstract_state;
    for ( auto &map_kv : map)
        abstract_state.emplace( move( map_kv.second));
#ifdef DEBUG
    cerr << "original state:" << endl;
    for ( auto const &group_kv : state.groups) {
        cerr << "\t" << group_kv.second.color << " : " << group_kv.first << endl;
    }
    cerr << "abstract state:" << endl;
    for ( GroupSet const &s : abstract_state) {
        cerr << "\t{ ";
        for ( GID const &id : s)
            cerr << id << ", ";
        cerr << " }" << endl;
    }
    auto find_it = state_set.find( abstract_state);
    if ( find_it != state_set.end()) {
        cerr << "find state:" << endl;
        for ( GroupSet const &s : *find_it) {
            cerr << "\t{ ";
            for ( GID const &id : s)
                cerr << id << ", ";
            cerr << " }" << endl;
        }
    } else {
        cerr << "new state!" << endl;
    }
#endif

    auto result = state_set.emplace( move( abstract_state));
#ifdef DEBUG
    if ( ! result.second)
        cerr << "dup state found." << endl;
#endif
    return result.second;
}


