#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#define NET_ID_LEN 16

struct Player
{
    int steam_id;
    char net_id[NET_ID_LEN];
    struct sockaddr_in addr;
    struct Position pos;
    struct Player *next;
};

int _compare_data(char *, char *, int);
void _push_player(char net_id[NET_ID_LEN], struct sockaddr_in);
void _pop_player(char net_id[NET_ID_LEN]);
struct Player *get_player(char net_id[NET_ID_LEN]);

#include "player.c"
#endif