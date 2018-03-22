#include "position.h"

// struct Position:

Position::Position( GID id)
    : x( id / WIDTH),
      y( id % WIDTH)
{
}

Position::Position( short x, short y)
    : x( x), y( y)
{
}

Position::Position( Position const &other)
    : x( other.x), y( other.y)
{
}

Position::~Position()
{
}

Position &
Position::operator=( Position const &rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

Position &
Position::operator=( GID id)
{
    x = id / WIDTH;
    y = id % WIDTH;
    return *this;
}

Position::operator bool() const
{
    if ( x < 0 || y < 0)
        return false;
    if ( x >= HEIGHT || y >= WIDTH)
        return false;
    return true;
}

bool
Position::point_left() const
{
    return ( x + y) % 2 == 1;
}

GID
Position::id() const
{
    return x * WIDTH + y;
}

