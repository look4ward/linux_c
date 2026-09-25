#ifndef _ex19_h
#define _ex19_h

#include "object.h"

typedef struct Monster {
    Object proto;
    int hit_points;
}Monster;

int Monster_attack(void *self, int damage);

typedef struct Room {
    Object proto;

    Monster *bad_guy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;

    int weapon;
}Room;


void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);


typedef struct Map {
    Object proto;
    Room *start;
    Room *location;
    int weapon;
}Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);

#endif
