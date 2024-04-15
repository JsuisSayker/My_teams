/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** find_command
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

    // {"/users", &users},
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

const struct function_tab_s OPERATORS_FUNCS[] = {
    {"/login", &login},
    {"/logout", &logout},
    // {"/user", &user},
    {NULL, NULL}
};

static int find_command_sub(server_data_t *server, client_server_t *client,
    int j, bool *is_found)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (strcmp(OPERATORS_FUNCS[j].str, client->user_input->command) == 0) {
        if (OPERATORS_FUNCS[j].flags(server, client) == ERROR)
            return ERROR;
    }
    return OK;
}

int find_command(server_data_t *server, client_server_t *client)
{
    bool is_found = false;

    if (server == NULL || client == NULL)
        return ERROR;
    for (int j = 0; strcmp(OPERATORS_FUNCS[j].str, "NULL") != 0; j++) {
        if (find_command_sub(server, client, j, &is_found) == ERROR)
            return ERROR;
    }
    if (is_found == false) {
        write(client->socket, "500 Command not found\n", 23);
        return OK;
    }
    if (client->user_input->command != NULL)
        free(client->user_input->command);
        client->user_input = NULL;
    return OK;
}
