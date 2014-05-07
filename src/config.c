#include <string.h>

void _save_default_config(void)
{
    errno = 0;
    FILE *handle = fopen("my.config", "w");
    if (errno != 0)
    {
        printf("Could not save default config! Errno = %d\n", errno);
        return;
    }
    fprintf(handle, "port: 2302\n");
    fprintf(handle, "max_players: 60\n");
    fprintf(handle, "server_name: Arma3 Server | SQF Sucks\n");
    fclose(handle);
}

void _read_line(char *ptr, int len, FILE *handle)
{
    int i;
    char reads;
    for (i = 0; i < len; i++)
    {
        ptr[i] = '\0';
    }
    for (i = 0; i < len; i++)
    {
        reads = (char) fgetc(handle);
        if (reads == '\n')
        {
            ptr[i] = '\0';
            break;
        }
        ptr[i] = reads;
    }
}

void _trim_beginning(char *str)
{
    int i, len = strlen(str), first_char_pos = 0;
    for (i = 0; i < len; i++)
    {
        if (first_char_pos == 0 && (str[i] != ' ' && str[i] != '\t'))
            first_char_pos = i;
    }
    for (i = 0; i < len; i++)
    {
        str[i] = str[i + first_char_pos];
    }
}

void load_config(struct Config *config)
{
    FILE *handle = fopen("my.config", "r");
    char line[CONFIG_LINE_MAX + 1], *key, *value;
    if (errno != 0)
    {
        printf("Failed to load config! Using defaults. Errno = %d\n", errno);
        config->port_no = 2302;
        config->max_players = 60;
        if (errno == 2)
            _save_default_config();
        return;
    }
    while (!feof(handle))
    {
        _read_line(line, CONFIG_LINE_MAX, handle);
        if (strlen(line) == 0 || line[0] == '#')
            continue;
        key = strtok(line, ":");
        value = strtok(NULL, ":");
        if (key == NULL || value == NULL)
            continue;
        _trim_beginning(value);
        if (strcmp(key, "port") == 0)
            config->port_no = atoi(value);
        else if (strcmp(key, "max_players") == 0)
            config->max_players = atoi(value);
        else if (strcmp(key, "server_name") == 0)
            strcpy(config->host_name, value);
        else
            printf("Unknown server setting `%s`!\n", key);
    }
    fclose(handle);
    printf("Config Options:\n  Port:\t\t%d\n  Max Players:\t%d\n", config->port_no, config->max_players);
}