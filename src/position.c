int len_d = sizeof (double);
int len_f = sizeof (float);

void add_position(struct Position *pos, struct Position amount)
{
    pos->x += amount.x;
    pos->y += amount.y;
    pos->z += amount.z;
    if (amount.yaw != pos->yaw || amount.pitch != pos->pitch)
    {
        pos->yaw = amount.yaw;
        pos->pitch = amount.pitch;
    }
}

char *to_byte(struct Position pos)
{
    int total_len = 0;
    char *ptr = (char *) malloc(len_d * 3 + len_f * 2);
    memcpy_full(ptr, (char *) &pos.x, total_len, len_d);
    total_len += len_d;
    memcpy_full(ptr, (char *) &pos.y, total_len, len_d);
    total_len += len_d;
    memcpy_full(ptr, (char *) &pos.z, total_len, len_d);
    total_len += len_d;
    memcpy_full(ptr, (char *) &pos.yaw, total_len, len_f);
    total_len += len_f;
    memcpy_full(ptr, (char *) &pos.pitch, total_len, len_f);
    return ptr;
}

struct Position *to_position(char *data)
{
    int i, total_len = 0;
    struct Position *ptr = (struct Position *) malloc(sizeof (struct Position));
    for (i = 0; i < 3; i++)
    {
        memcpy_full(data, (char *) ptr, total_len, len_d);
        total_len += len_d;
    }
    for (i = 0; i < 2; i++)
    {
        memcpy_full(data, (char *) ptr, total_len, len_f);
        total_len += len_f;
    }
    return ptr;
}