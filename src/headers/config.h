#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_LINE_MAX 128

struct Config
{
    int port_no, max_players;
    char host_name[128];
};

void _save_default_config(void);
void _read_line(char *, int, FILE *);
void _trim_beginning(char *);
void load_config(struct Config *);

#include "config.c"
#endif