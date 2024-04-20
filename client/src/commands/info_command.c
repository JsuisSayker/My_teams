/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** info_command
*/

#include "client.h"

static int info_command_sub(char **command)
{
    if (strcmp(command[2], "channel") == 0) {
            client_print_channel(command[3], command[4], command[5]);
        return OK;
    }
    if (strcmp(command[2], "reply") == 0) {
        client_print_thread(command[3], command[4],
            convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
            command[6], command[7]);
        return OK;
    }
    return OK;
}

int info_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    if (strcmp(command[2], "user") == 0) {
        client_print_user(command[3], command[4], atoi(command[5]));
        return OK;
    }
    if (strcmp(command[2], "team") == 0) {
        client_print_team(command[3], command[4], command[5]);
        return OK;
    }
    info_command_sub(command);
    return OK;
}
