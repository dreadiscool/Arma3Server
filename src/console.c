void _print_help()
{
    printf("Printing command help\n");
    printf("  lock_on  : Prevents players from joining\n");
    printf("  lock_off : Allows player to join again\n");
    printf("  end      : Ends the server process immidiately\n");
    printf("  kick <p> : Kicks player `p` off the server\n");
    printf("  ban <p>  : Bans steamid of player `p`\n");
    printf("\n");
}

void handle_console_command(char *cmd)
{
    if (strcmp("end", cmd) == 0)
    {
        printf("Process aborting on request by user\n");
        exit(1);
    }
    else if (strcmp("help", cmd) == 0)
        _print_help();
    else if (strcmp("player_count", cmd) == 0)
        printf("Player Count: %d\n", player_count);
    else
        printf("Unknown command!\n");
}