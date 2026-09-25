#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"
#include "object.h"

#define  defult_damage  2

int Monster_init(void *self)
{
    assert(self != NULL);
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};

int Map_init(void *self)
{
    assert(self != NULL);
    Map *map = self;
    // make some rooms for a small map
    Room *hall = NEW(Room, "The great Hall");
    //object_new(sizeof(Room), Roomproto, "The gteat Hall"
    assert(hall != NULL);
    Room *throne = NEW(Room, "The throne room");
    assert(throne != NULL);
    Room *arena = NEW(Room, "The arena, with the minotaur");
    assert(arena != NULL);
    Room *kitchen = NEW(Room, "Kitchen, there's knife, do you want it?\nY/N");
    assert(kitchen != NULL);

    Room *office = NEW(Room, "The office, there's gun, do you want it?\nY/N");
    assert(hall != NULL);

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    assert(arena->bad_guy != NULL);

    // setup the map rooms
    hall->north = throne;
    hall->south = NULL;
    hall->west = NULL;
    hall->east = NULL;
                           //                   office 
    throne->north = office;//                      | 
    throne->west = arena;//             arena<--throne-->kichten
    throne->east = kitchen;//                      |     
    throne->south = hall;//                       hall

    kitchen->north = NULL;
    kitchen->south = NULL;
    kitchen->west = throne;
    kitchen->east = NULL;

    arena->north = NULL;
    arena->south = NULL;
    arena->west = NULL;
    arena->east = throne;

    office->north = NULL;
    office->south = throne;
    office->west = NULL;
    office->east = NULL;
    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;
    
    // setup player's damage
    map->weapon = defult_damage;
    // setup room's weapon damage
    hall->weapon = defult_damage;
    arena->weapon = defult_damage;
    throne->weapon = defult_damage;
    kitchen->weapon = 5;
    office->weapon = 10;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    assert(game != NULL);
    assert(game->proto.move != NULL);
    assert(game->location != NULL);
    printf("\n> ");

    char ch = getchar();
    getchar(); // eat ENTER

    switch(ch) {
        case -1://文件结束符EOF，值为-1
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            game->_(attack)(game, game->weapon);
            break;
        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;
        case 'Y':
            game->weapon = game->location->weapon;
            printf("You hit points are %d.\n", game->weapon);
            break;
        case 'N':
            break;

        default:
            printf("What?: %d\n", ch);
    }

    return 1;
}

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");
    assert(game != NULL);

    printf("You enter the ");
    assert(game->location != NULL);
    assert(game->location->proto.describe != NULL);
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }

    return 0;
}
