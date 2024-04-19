/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** users_command
*/

#include <stdio.h>

#include "client.h"

static int display_users_command(char **command)
{
    int tab_length = my_tablen(command);

    if (command == NULL || tab_length == ERROR)
        return ERROR;
    for (int i = 2; i < tab_length; i += 3){
        if (strcmp(command[i + 2], "1") == OK)
            client_print_users(command[i + 1], command[i], CONNECTED);
        else
            client_print_users(command[i + 1], command[i], DISCONNECTED);
    }
    return OK;
}

int users_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    } else {
        if (display_users_command(command) == ERROR)
            return ERROR;
        return OK;
    }
    return OK;
}
