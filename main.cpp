#include <iostream>
#include <fstream>
#include <chrono>
#include <set>

#include "kami_state.h"
#include "distance_map.h"
#include "state_record.h"

using namespace std;

constexpr int MAX_STEP = 6;
constexpr int MIN_STEP = 6;

struct Result {
    GID gid;
    char original_color, color;
};

int dfs( KamiState const &original_state, Result *result, int max_step, StateRecord &record)
{
    if ( original_state.groups.size() <= 1)
        return 0;
    set<char> colors;
    for ( auto const &kv : original_state.groups)
        colors.insert( kv.second.color);
    // consider un-connected graph:
    if ( colors.size() <= 1)
        return 0;
    if ( colors.size() > unsigned( max_step + 1))
        return -1;

    if ( ! record.check_and_insert( original_state))
        return -1;

    bool has_usable_color = false;
    DistanceMap distance;

    // for each group:
    for ( auto const &group_kv : original_state.groups) {
        GID gid = group_kv.first;

        // cut-branch by eccentricity:
        if ( distance.eccentricity( original_state, gid) > max_step)
            continue;

        // list all colors that make sense to change to:
        set<char> usable_colors;
        for ( auto const &edge_kv : original_state.edges) {
            GID adjacent_gid = -1;
            if ( edge_kv.first == gid)
                adjacent_gid = edge_kv.second;
            else if ( edge_kv.second == gid)
                adjacent_gid = edge_kv.first;
            if ( adjacent_gid >= 0) {
                usable_colors.insert( original_state.groups.at( adjacent_gid).color);
                has_usable_color = true;
            }
        } // for each edge

        // try to change to each color:
        for ( auto const &color : usable_colors) {
            KamiState state( original_state);
            Group &group = state.groups[ gid];

            result->gid = gid;
            result->color = color;
            result->original_color = group.color;

            group.color = color;
            state.merge_group();
            int ret = dfs( state, result + 1, max_step - 1, record);
            if ( ret >= 0) {
#ifdef DEBUG
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
        } // for each usable color
    } // for each group

    // consider un-connected graph:
    if ( ! has_usable_color) {
        for ( auto const &group_kv : original_state.groups) {
            GID gid = group_kv.first;
            for ( auto const &color : colors)
                if ( group_kv.second.color != color) {
                    KamiState state( original_state);
                    Group &group = state.groups[ gid];

                    result->gid = gid;
                    result->color = color;
                    result->original_color = group.color;

                    group.color = color;
                    state.merge_group();
                    int ret = dfs( state, result + 1, max_step - 1, record);
                    if ( ret >= 0)
                        return ret + 1;
                }
        } // for each group
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
    for ( int max_step = MIN_STEP; max_step <= MAX_STEP; max_step ++) {
        cout << "trying to solve in " << max_step << " step(s)..." << endl;
        StateRecord record;
        int ret = dfs( state, result, max_step, record);
        if ( ret >= 0) {
            cout << "Solution Found:" << endl;
            cout << "\t---------------------" << endl;
            for ( int i = 0; i < ret; i ++) {
                Position pos( result[ i].gid);
                cout << "\t( " << pos.x + 1 << " , " << pos.y + 1 << " ) : "
                    << result[ i].original_color << " -> "
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

