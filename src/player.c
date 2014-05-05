int player_count = 0;

struct Player *root = NULL;
struct Player *curr = NULL;

int _compare_data(char *ptr1, char *ptr2, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (ptr1[i] != ptr2[2])
            return -1;
    }
    return 0;
}

void _push_player(char net_id[NET_ID_LEN], struct sockaddr_in addr)
{
    struct Player *current = root, *player = (struct Player *) malloc(sizeof (struct Player));
    memcpy(player->net_id, net_id, NET_ID_LEN);
    memcpy(&(player->addr), &addr, sizeof (struct sockaddr_in));
    player->next = NULL;
    if (root == NULL)
        root = curr = player;
    else
    {
        curr->next = player;
        curr = player;
    }
    player_count++;
}

void _pop_player(char net_id[NET_ID_LEN])
{
    struct Player *previous = NULL;
    struct Player *current = root;
    while (current != NULL)
    {
        if (_compare_data(current->net_id, net_id, NET_ID_LEN))
        {
            previous->next = current->next;
            free(current);
            player_count--;
            return;
        }
        current = current->next;
    }
    printf("Non-Fatal: Attempted to pop player from stack that didn't exist!\n");
}

struct Player *get_player(char net_id[NET_ID_LEN])
{
    struct Player *current = root;
    while (current != NULL)
    {
        printf("%s\0\n", current->net_id);
        if (_compare_data(current->net_id, net_id, NET_ID_LEN))
            return current;
    }
    return NULL;
}