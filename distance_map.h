#ifndef _DISTANCE_MAP_H
#define _DISTANCE_MAP_H

#include "position.h"

struct KamiState;

class DistanceMap {
    public:
        enum {
            NOT_CALCULATED = -1,
            UNREACHABLE = 0,
        };
    private:
        static constexpr unsigned MAX_GROUP_COUNT
            = Position::HEIGHT * Position::WIDTH;

        int record[ MAX_GROUP_COUNT][ MAX_GROUP_COUNT];
        void _calculate_distance( KamiState const &state, GID gid);
        
    public:
        DistanceMap();
        int distance( KamiState const &state, GID gid1, GID gid2);
        int eccentricity( KamiState const &state, GID gid);
};

#endif

