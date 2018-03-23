
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

    auto result = state_set.emplace( move( abstract_state));
    return result.second;
}


