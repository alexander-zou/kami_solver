#ifndef STATE_RECORD_H
#define STATE_RECORD_H

#include <unordered_set>
#include <unordered_map>

#include "position.h"
#include "kami_state.h"

class StateRecord {
    public:
        typedef std::unordered_set<GID> GroupSet;
        typedef std::unordered_map<char,GroupSet> ColorMap;
        typedef std::unordered_set<GroupSet> AbstractState;
        typedef std::unordered_set<AbstractState> StateSet;

    private:
        StateSet state_set;

    public:
        void clear();
        bool check_and_insert( KamiState const &state);
};

#endif


