#ifndef POSITION_H
#define POSITION_H

struct Position
{
    double x, y, z;
    float yaw, pitch;
};

void add_position(struct Position *, struct Position);
char *to_byte(struct Position);
struct Position *to_position(char *);

#include "position.c"
#endif