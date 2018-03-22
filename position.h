#ifndef POSITION_H
#define POSITION_H

typedef short GID;

struct Position {
    static constexpr int HEIGHT = 29;
    static constexpr int WIDTH = 10;
    short x, y;
    Position( short x, short y);
    Position( Position const &other);
    Position( GID id = 0);
    ~Position();
    Position &operator=( Position const &rhs);
    Position &operator=( GID id);
    operator bool() const;
    bool point_left() const;
    GID id() const;
};

#endif


