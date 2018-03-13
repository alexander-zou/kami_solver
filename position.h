#ifndef POSITION_H
#define POSITION_H

struct Position {
    static constexpr int HEIGHT = 29;
    static constexpr int WIDTH = 10;
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

#endif


