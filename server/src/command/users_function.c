/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** users_function
*/

#include "server.h"

static int users_command_response(list_user_t *list, int socket)
{
    char *message = NULL;

    append_to_string(&message, "200 /users ");
    if (list == NULL)
        return ERROR;
    for (list_user_t *tmp = list; tmp != NULL; tmp = tmp->next) {
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
    list_user_t *list = NULL;

    if (client == NULL || server == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\n\r", 23);
        return OK;
    }
    LIST_FOREACH(server->users.lh_first, &server->users, entries) {
        list = add_node_in_list(list, server->users.lh_first->username,
            server->users.lh_first->description);
    }
    if (list == NULL){
        write(client->socket, "500, No users found\n\r", 22);
        return OK;
    }
    if (users_command_response(list, client->socket) == ERROR)
        return ERROR;
    free_list(list);
    return OK;
}

static int user_command_response(user_t *user, int socket)
{
    char *message = NULL;

    append_to_string(&message, "200 /user ");
    append_to_string(&message, user->username);
    append_to_string(&message, "|");
    append_to_string(&message, user->description);
    append_to_string(&message, "\a\n");
    if (server_response(socket, message) == ERROR)
        return ERROR;
    return OK;
}

int user(server_data_t *server, client_server_t *client)
{
    user_t *tmp;

    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\a\n\0", 24);
        return OK;
    }
    tmp = get_user_by_uuid(server, client->command->params->user_uuid);
    if (tmp == NULL)
        return ERROR;
    if (user_command_response(tmp, client->socket) == ERROR)
        return ERROR;
    return OK;
}
