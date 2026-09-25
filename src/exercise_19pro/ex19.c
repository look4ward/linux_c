#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"


int Monster_attack(void *self, int damage)
{
    assert(self != NULL);
    Monster *monster = self;

    assert(monster->proto.description != NULL);
    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0) {
        printf("hit %d damage. It still has %dhp.\n", damage, monster->hit_points);
        return 0;
    } else {
        printf("hit %d damage. It is dead!\n", damage);
        return 1;
    }
}

void *Room_move(void *self, Direction direction)
{
    assert(self != NULL);
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if(direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if(direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if(next) {
        if(next->proto.describe != NULL);
        next->_(describe)(next);//next->proto.describe(next)
    }

    return next;
}


int Room_attack(void *self, int damage)
{
    assert(self != NULL);
    Room *room = self;
    Monster *monster = room->bad_guy;

    if(monster) {
        assert(monster->proto.attack != NULL);
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);
    Map *map = self;
    Room *location = map->location;
    assert(location != NULL);
    Room *next = NULL;

    assert(location->proto.move != NULL);
    next = location->_(move)(location, direction);//location->proto.move(location, direction)

    if(next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);
    Map* map = self;
    Room *location = map->location;
    assert(location != NULL);
    assert(location->proto.attack != NULL);
    return location->_(attack)(location, damage);
}

