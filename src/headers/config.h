#ifndef CONFIG_H
#define CONFIG_H

struct Config
{
    int port_no, max_players;
};

void _save_default_config(void);
void load_config(struct Config *);

#include "config.c"
#endif