#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "util.h"
#include "position.h"
#include "config.h"
#include "player.h"
#include "network.h"
#include "console.h"

#define CONSOLE_CMD_MAX 1024

struct Config server_config;
int server_fd;

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("==================================================\n");
    printf("| SIGSEGV (Segfault) FATAL ERROR!                |\n");
    printf("==================================================\n");
    printf("| Unfortunately, arma3server has encountered an  |\n");
    printf("| error and must close. Please report this on    |\n");
    printf("| http://github.com/Arma3Server and post what    |\n");
    printf("| you think caused this error                    |\n");
    printf("==================================================\n");
    exit(-1);
}

void set_segfault_handler()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof (sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);
}

int main()
{
    pthread_t network_thread;
    char msg_buf[CONSOLE_CMD_MAX + 1];
    set_segfault_handler();
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