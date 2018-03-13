#include <iostream>
#include <fstream>
#include <chrono>
#include <set>

#include "kami_state.h"

using namespace std;

constexpr int MAX_STEP = 30;

struct Result {
    int gid;
    char color;
};

// TODO: use foreach instead of iter:
int dfs( KamiState const &original_state, Result *result, int max_step)
{
    if ( original_state.groups.size() <= 1)
        return 0;
    if ( max_step <= 0)
        return -1;
    // cut impossible state:
    {
        set<char> colors;
        for ( auto const &kv : original_state.groups)
            colors.insert( kv.second.color);
        if ( colors.size() > max_step + 1)
            return -1;
    }

    // for each group:
    for ( auto group_it = original_state.groups.begin(); group_it != original_state.groups.end(); ++ group_it) {
        int gid = group_it->first;

        // list all colors that make sense to change to:
        set<char> usable_colors;
        for ( auto edge_it = original_state.edges.begin(); edge_it != original_state.edges.end(); ++ edge_it) {
            int adjacent_gid = -1;
            if ( edge_it->first == gid)
                adjacent_gid = edge_it->second;
            else if ( edge_it->second == gid)
                adjacent_gid = edge_it->first;
            if ( adjacent_gid >= 0)
                usable_colors.insert( original_state.groups.at( adjacent_gid).color);
        }

        // try to change to each color:
        for ( auto it = usable_colors.begin(); it != usable_colors.end(); ++ it) {
            KamiState state( original_state);
            state.groups[ gid].color = *it;
            state.merge_group();
            result->gid = gid;
            result->color = *it;
            
            int ret = dfs( state, result + 1, max_step - 1);
            if ( ret >= 0) {
#if 0 // debug:
                cout << "-------" << endl;
                cout << "groups: " << state.groups.size() << endl;
                for ( auto const &kv : state.groups) {
                    Position pos( kv.first);
                    cout << " id: " << kv.first << ", x: " << pos.x << ", y: " << pos.y << ", color: " << kv.second.color << endl;
                }
                cout << "edges: " << state.edges.size() << endl;
                for ( auto const &edge : state.edges) {
                    cout << " (" << edge.first << "," << edge.second << ")";
                }
                cout << endl;
                cout << "-------" << endl;
#endif
                return ret + 1;
            }
        }
    }
    return -1;
}

int main( int argc, char **argv)
{
    KamiState state;
    if ( argc > 1) {
        ifstream fin( argv[ 1]);
        state = KamiState::read_state( fin);
    } else {
        state = KamiState::read_state( cin);
    }
    auto start_time = chrono::high_resolution_clock::now();
    Result result[ MAX_STEP];
    for ( int max_step = 1; max_step <= MAX_STEP; max_step ++) {
        cout << "trying to solve in " << max_step << " step(s)..." << endl;
        int ret = dfs( state, result, max_step);
        if ( ret >= 0) {
            cout << "Solution Found:" << endl;
            cout << "\t---------------------" << endl;
            for ( int i = 0; i < ret; i ++) {
                Position pos( result[ i].gid);
                cout << "\t( " << pos.x + 1 << " , " << pos.y + 1 << " ) -> "
                    << result[ i].color << endl;
            }
            cout << "\t---------------------" << endl;
            break;
        }
    }
    auto finish_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_used = finish_time - start_time;
    cout << "Time Used: " << time_used.count() << " s" << endl;
    return 0;
}

