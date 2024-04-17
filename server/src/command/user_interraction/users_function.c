/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** users_function
*/

#include "server.h"

static int users_command_response(list_t *list, int socket)
{
    char *message = NULL;

    append_to_string(&message, "200 /users ");
    if (list == NULL)
        return ERROR;
    for (list_t *tmp = list; tmp != NULL; tmp = tmp->next) {
        append_to_string(&message, tmp->username);
        append_to_string(&message, "|");
        append_to_string(&message, tmp->description);
        if (tmp->next != NULL)
            append_to_string(&message, " ");
    }
    append_to_string(&message, "\a\n");
    if (server_response(socket, message) == ERROR)
        return ERROR;
    return OK;
}

int users(server_data_t *server, client_server_t *client)
{
    list_t *list = NULL;

    if (client == NULL || server == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\n\r", 59);
        return OK;
    }
    LIST_FOREACH(server->users.lh_first, &server->users, entries) {
        add_node_in_list(list, server->users.lh_first->username,
            server->users.lh_first->description);
    }
    if (users_command_response(list, client->socket) == ERROR)
        return ERROR;
    return OK;
}
