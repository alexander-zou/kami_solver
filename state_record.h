#ifndef STATE_RECORD_H
#define STATE_RECORD_H

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "position.h"
#include "kami_state.h"

class StateRecord {
    public:
        typedef std::set<GID> GroupSet;
        typedef std::map<char,GroupSet> ColorMap;
        typedef std::set<GroupSet> AbstractState;
        typedef std::set<AbstractState> StateSet;

    private:
        StateSet state_set;

    public:
        void clear();
        bool check_and_insert( KamiState const &state);
};

#endif


