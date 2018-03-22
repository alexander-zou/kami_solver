#include <vector>

#include "distance_map.h"
#include "kami_state.h"

using namespace std;

DistanceMap::DistanceMap()
{
    for ( unsigned i = 0; i < MAX_GROUP_COUNT; i ++)
        for ( unsigned j = 0; j < MAX_GROUP_COUNT; j ++)
            record[ i][ j] = NOT_CALCULATED;
}

void
DistanceMap::_calculate_distance( KamiState const &state, int gid)
{
    int step = 1;
    set<int> reached_gids{ gid}
    set<int> curr_gids{ gid}, next_gids;
    do {
        // TODO
    } while ( curr_gids.size());
}

int
DistanceMap::distance( KamiState const &state, int gid1, int gid2)
{
    if ( record[ gid1][ gid2] == NOT_CALCULATED)
        _calculate_distance( state, gid1);
    return record[ gid1][ gid2];
}

int
DistanceMap::eccentricity( KamiState const &state, int gid)
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



