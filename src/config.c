void _save_default_config(void)
{
    errno = 0;
    FILE *handle = fopen("my.config", "w");
    if (errno != 0)
    {
        printf("Could not save default config! Errno = %d\n", errno);
        return;
    }
    fprintf(handle, "port: 2302");
    fprintf(handle, "max_players: 60");
    fclose(handle);
}

void load_config(struct Config *config)
{
    FILE *handle = fopen("my.config", "r");
    if (errno != 0)
    {
        printf("Failed to load config! Using defaults. Errno = %d\n", errno);
        config->port_no = 2302;
        config->max_players = 60;
        if (errno == 2)
            _save_default_config();
        return;
    }
    fscanf(handle, "port: %d", &(config->port_no));
    fscanf(handle, "max_players: %d", &(config->max_players));
    fclose(handle);
    if (config->port_no == 0)
        config->port_no = 2302;
    if (config->max_players == 0)
        config->max_players = 60;
    printf("Config Options:\n  Port:\t\t%d\n  Max Players:\t%d\n", config->port_no, config->max_players);
}