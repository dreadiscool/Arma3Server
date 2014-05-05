void memcpy_full(char *dst, char *src, int start_pos, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        dst[i] = src[start_pos + i];
    }
}