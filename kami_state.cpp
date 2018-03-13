
#include "kami_state.h"

using namespace std;

// struct Position:

Position::operator bool() const
{
    if ( x < 0 || y < 0)
        return false;
    if ( x >= KamiState::HEIGHT || y >= KamiState::WIDTH)
        return false;
    return true;
}

bool
Position::point_left() const
{
    return ( x + y) % 2 == 1;
}

int
Position::id() const
{
    return x * KamiState::WIDTH + y;
}

// struct Group:


// struct KamiState:

KamiState::KamiState()
{
}

KamiState::~KamiState()
{
}

KamiState::KamiState( KamiState const &other)
    : groups( other.groups),
      edges( other.edges)
{
}

KamiState &
KamiState::operator=( KamiState const &rhs)
{
    groups = rhs.groups;
    edges = rhs.edges;
    return *this;
}

void
KamiState::merge_group()
{
    bool finished;
    do {
        finished = true;
        for ( auto it = edges.begin(); it != edges.end(); ++ it) {
            int id1 = it->first;
            Group &g1 = groups[ id1];
            int id2 = it->second;
            Group &g2 = groups[ id2];
            if ( g1.color == g2.color) {
                set<Edge> new_edges;
                for ( it = edges.begin(); it != edges.end(); ++ it) {
                    if ( it->first == id1 && it->second == id2)
                        continue;
                    else if ( it->first == id2 && it->second == id1)
                        continue;
                    else if ( it->first == id2)
                        new_edges.insert( id1 < it->second
                                            ? make_pair( id1, it->second)
                                            : make_pair( it->second, id1));
                    else if ( it->second == id2)
                        new_edges.insert( id1 < it->first
                                            ? make_pair( id1, it->first)
                                            : make_pair( it->first, id1));
                    else
                        new_edges.insert( *it);
                }
                edges = move( new_edges);
                groups.erase( id2);
                finished = false;
                break; // for checking each edge
            } // if
        } // for
    } while ( ! finished);
}

KamiState
KamiState::read_state( istream &in)
{
    KamiState state;
    char ch;
    int id = 0;
    while ( in >> ch) {
        if ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
            continue;
        else if ( id >= WIDTH * HEIGHT)
            break;
        else {
            int x = id / WIDTH;
            int y = id % WIDTH;
            Group group{ ch, { x, y}};
            state.groups.insert( make_pair( id, group));
            if ( group.position.point_left()) {
                Position position;
                position.x = group.position.x - 1;
                position.y = group.position.y;
                if ( position)
                    state.edges.insert( make_pair( position.id(), id));
            } else {
                Position position;
                position.x = group.position.x - 1;
                position.y = group.position.y;
                if ( position)
                    state.edges.insert( make_pair( position.id(), id));
                position.x = group.position.x;
                position.y = group.position.y - 1;
                if ( position)
                    state.edges.insert( make_pair( position.id(), id));
            }
            id ++;
        }
    }
    state.merge_group();
    return state;
}


