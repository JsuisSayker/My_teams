/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** list_command
*/

#include "client.h"

static int list_command_sub(char **command)
{
    if (strcmp(command[2], "thread") == 0) {
        for (int i = 3; command[i]; i += 5) {
            client_channel_print_threads(command[i], command[i + 1],
                convert_string_to_time_t(command[i + 2],
                "%a %b %d %H:%M:%S %Y"), command[i + 3], command[i + 4]);
        }
        return OK;
    }
    if (strcmp(command[2], "reply") == 0) {
        for (int i = 3; command[i]; i += 4) {
            client_thread_print_replies(command[i], command[i + 1],
                convert_string_to_time_t(command[i + 2],
                "%a %b %d %H:%M:%S %Y"), command[i + 3]);
        }
        return OK;
    }
    return OK;
}

int list_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    if (strcmp(command[2], "team") == 0) {
        for (int i = 3; command[i]; i += 3)
            client_print_teams(command[i], command[i + 1], command[i + 2]);
        return OK;
    }
    if (strcmp(command[2], "channel") == 0) {
        for (int i = 3; command[i]; i += 3)
            client_team_print_channels(command[i], command[i + 1],
                command[i + 2]);
        return OK;
    }
    list_command_sub(command);
    return OK;
}
