#include <set>
#include <unordered_set>

#include "distance_map.h"
#include "kami_state.h"

using namespace std;

DistanceMap::DistanceMap()
{
    for ( unsigned i = 0; i < MAX_GROUP_COUNT; i ++)
        for ( unsigned j = 0; j < MAX_GROUP_COUNT; j ++)
            record[ i][ j] = NOT_CALCULATED;
}

template<typename C, typename V>
inline bool contains( C const &c, V const &v)
{
    return c.find( v) != c.end();
}

void
DistanceMap::_calculate_distance( KamiState const &state, GID gid)
{
    int step = 1;
    unordered_set<GID> reached_gids{ gid};
    unordered_set<GID> curr_gids{ gid}, next_gids;
    do {
        for ( auto const &edge : state.edges) {
            GID connect_gid = -1;
            if ( contains( curr_gids, edge.first) && ! contains( reached_gids, edge.second))
                connect_gid = edge.second;
            else if ( contains( curr_gids, edge.second) && ! contains( reached_gids, edge.second))
                connect_gid = edge.first;
            if ( connect_gid >= 0) {
                record[ gid][ connect_gid] = 
                record[ connect_gid][ gid] = step;
                next_gids.insert( connect_gid);
                reached_gids.insert( connect_gid);
            }
        }
        step ++;
        curr_gids = move( next_gids);
    } while ( curr_gids.size());
}

int
DistanceMap::distance( KamiState const &state, GID gid1, GID gid2)
{
    if ( record[ gid1][ gid2] == NOT_CALCULATED)
        _calculate_distance( state, gid1);
    return record[ gid1][ gid2];
}

int
DistanceMap::eccentricity( KamiState const &state, GID gid)
{
    int result = 0;
    for ( auto const &kv : state.groups)
        if ( kv.first != gid) {
            int dis = distance( state, gid, kv.first);
            if ( dis > 0 && dis > result)
                result = dis;
        }
    return result;
}



