/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** find_command
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

const struct function_tab_s OPERATORS_FUNCS[] = {
    {"/login", &login},
    // {"/logout", &logout},
    // {"/users", &users},
    // {"/user", &user},
    // {"/send", &send},
    // {"/messages", &messages},
    // {"/subscribe", &subscribe},
    // {"/subscribed", &subscribed},
    // {"/unsubscribe", &unsubscribe},
    // {"/use", &use},
    // {"/create", &create},
    // {"/list", &list},
    // {"/info", &info},
    // {"/help", &help},
    {NULL, NULL}
};

static int find_command_sub(server_data_t *server, user_t *user,
    int j, bool *is_found)
{
    if (server == NULL || user == NULL)
        return KO;
    if (strcmp(OPERATORS_FUNCS[j].str, user->command[0]) == 0) {
        if (OPERATORS_FUNCS[j].flags(server, user) == KO)
            return KO;
    }
    return OK;
}

int find_command(server_data_t *server, user_t *user)
{
    bool is_found = false;

    if (server == NULL || user == NULL)
        return ERROR;
    for (int j = 0; strcmp(OPERATORS_FUNCS[j].str, "NULL") != 0; j++) {
        if (find_command_sub(server, user, j, &is_found) == KO)
            return KO;
    }
    if (is_found == false) {
        dprintf(user->socket, "500 Command not found\n");
        return KO;
    }
    if (user->command != NULL)
        free(user->command);
    return OK;
}
