/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** subscribed_command
*/

#include "client.h"

static void client_print_team_subscribed(char **command)
{
    for (int i = 3; command[i] != NULL; i += 3) {
        client_print_teams(command[i], command[i + 1], command[i + 2]);
    }
}

static void client_print_user_subscribed(char **command)
{
    for (int i = 3; command[i] != NULL; i += 4) {
        client_print_users(command[i], command[i + 1], atoi(command[i + 3]));
    }
}

int subscribed_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    if (strcmp(command[2], "/teams") == 0) {
        client_print_team_subscribed(command);
        return OK;
    } else if (strcmp(command[2], "/users") == 0) {
        client_print_user_subscribed(command);
        return OK;
    }
    return OK;
}
