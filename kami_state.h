#ifndef KAMI_STATE_H
#define KAMI_STATE_H

#include <istream>
#include <map>
#include <set>

#include "position.h"

using namespace std;

typedef pair< GID, GID> Edge;

struct Group {
    char color;
    Position position;
};

struct KamiState {
    static constexpr char BLOCK_COLOR = '*';

    map< GID, Group> groups;
    set< Edge> edges;

    KamiState();
    KamiState( KamiState const &other);
    ~KamiState();

    KamiState &operator=( KamiState const &rhs);

    void merge_group();

    static KamiState read_state( istream &in);
};


#endif // KAMI_STATE_H


