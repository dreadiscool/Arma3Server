#ifndef NETWORK_H
#define NETWORK_H

#define CLI_BUF_SIZE 1024

/* Opcodes */
#define OP_CONN_REQ     0
#define OP_CONN_DC      1
#define OP_PLAYER_MOVE  2

void *recv_net_data(void *);
void start_listening(struct Config *, int *);

#include "network.c"
#endif