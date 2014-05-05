#include "util.h"
#include "position.h"

void *recv_net_data(void *arg)
{
    struct sockaddr_in client_addr;
    struct Player *player;
    char buf[CLI_BUF_SIZE], client_session_id[16], opcode, packet[CLI_BUF_SIZE - 17], ip_str[65];
    socklen_t len;
    int n, fd;
    memcpy(&fd, (int *) arg, sizeof (int));
    while (1)
    {
        len = sizeof (client_addr);
        n = recvfrom(fd, buf, CLI_BUF_SIZE, 0, (struct sockaddr *) &client_addr, &len);
        memcpy_full(client_session_id, buf, 0, 16);
        opcode = buf[16];
        memcpy_full(packet, buf, 17, n - 17);
        inet_ntop(AF_INET, &(client_addr.sin_addr), ip_str, len);
        if (n < 0)
        {
            printf("Error receiving data! Errno = %d\n", errno);
            continue;
        }
        if (n < 17)
        {
            printf("Invalid packet length %d from `%s`!\n", n, ip_str);
            continue;
        }
        player = get_player(client_session_id);
        if (player == NULL)
        {
            if (opcode == OP_CONN_REQ)
            {
                _push_player(client_session_id, client_addr);
                printf("Incoming connection from `%s`.\n", ip_str);
            }
            else
                printf("Unknown opcode `%c` from `%s`", opcode, ip_str);
        }
        else
        {
            if (opcode == OP_CONN_DC)
            {
                _pop_player(client_session_id);
                printf("`%s` is disconnecting from the server.\n", ip_str);
            }
            else if (opcode == OP_PLAYER_MOVE)
            {
                struct Position *old = &(player->pos);
                struct Position *new = to_position(packet);
            }
        }
    }
}

void start_listening(struct Config *config, int *ptr_fd)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    socklen_t len;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(config->port_no);
    if (fd < 0)
    {
        printf("Failed to create socket!\n", errno);
        exit(-1);
    }
    if (bind(fd, (struct sockaddr *)&server_addr, sizeof (server_addr)) < 0)
    {
        printf("Failed to bind to port %d! Errno = %d\n", config->port_no, errno);
        exit(-1);
    }
    memcpy(ptr_fd, &fd, sizeof (int));
    printf("Now listening on UDP port %d for clients!\n", config->port_no);
}