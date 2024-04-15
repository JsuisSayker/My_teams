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

static int find_command_sub(server_data_t *server, client_t *client,
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

int find_command(server_data_t *server, client_t *client)
{
    bool is_found = false;

    if (server == NULL || client == NULL)
        return ERROR;
    for (int j = 0; strcmp(OPERATORS_FUNCS[j].str, "NULL") != 0; j++) {
        if (find_command_sub(server, client, j, &is_found) == KO)
            return KO;
    }
    if (is_found == false) {
        dprintf(client->socket, "500 Command not found\n");
        return KO;
    }
    if (client->command != NULL)
        free(client->command);
    return OK;
}
