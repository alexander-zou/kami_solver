#ifndef KAMI_STATE_H
#define KAMI_STATE_H

#include <istream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Position {
    int x, y;
    Position( int x, int y);
    Position( Position const &other);
    Position( int id = 0);
    ~Position();
    Position &operator=( Position const &rhs);
    Position &operator=( int id);
    operator bool() const;
    bool point_left() const;
    int id() const;
};

typedef pair< int, int> Edge;

struct Group {
    char color;
    Position position;
};

struct KamiState {
    static constexpr int HEIGHT = 29;
    static constexpr int WIDTH = 10;
    static constexpr char BLOCK_COLOR = '*';

    map< int, Group> groups;
    set< Edge> edges;

    KamiState();
    KamiState( KamiState const &other);
    ~KamiState();

    KamiState &operator=( KamiState const &rhs);

    void merge_group();

    static KamiState read_state( istream &in);
};


#endif // KAMI_STATE_H


