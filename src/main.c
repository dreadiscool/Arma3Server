#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"
#include "position.h"
#include "config.h"
#include "player.h"
#include "network.h"
#include "console.h"

#define CONSOLE_CMD_MAX 1024

struct Config server_config;
int server_fd;

int main()
{
    pthread_t network_thread;
    char msg_buf[CONSOLE_CMD_MAX + 1];
    load_config(&server_config);
    start_listening(&server_config, &server_fd);
    pthread_create(&network_thread, NULL, recv_net_data, (void *) &server_fd);
    while (1)
    {
        if (fgets(msg_buf, CONSOLE_CMD_MAX, stdin) == NULL)
        {
            printf("Server process is terminating...\n");
            pthread_join(network_thread, (void *) NULL);
            printf("Finished\n");
            exit(1);
        }
        msg_buf[strlen(msg_buf) - 1] = '\0';
        handle_console_command((char *) msg_buf);
    }
}