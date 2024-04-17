/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login_logout
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

static int already_exist(server_data_t *server, client_server_t *client,
    char *name)
{
    user_t *tmp;

    client->user = malloc(sizeof(user_t));
    if (server == NULL || client == NULL || name == NULL)
        return ERROR;
    tmp = server->users.lh_first;
    if (tmp == NULL)
        return ERROR;
    LIST_FOREACH(tmp, &server->users, entries) {
        if (strcmp(tmp->username, name) == 0) {
            break;
        }
    }
    client->user->username = strdup(tmp->username);
    client->user->uuid = strdup(tmp->uuid);
    if (tmp->description != NULL)
        client->user->description = strdup(tmp->description);
    client->user->description = NULL;
    client->is_logged = true;
    return ERROR;
}

static int login_response(int socket, user_t *user)
{
    char *message = NULL;

    if (user == NULL)
        return ERROR;
    append_to_string(&message, "200 /login ");
    append_to_string(&message, user->username);
    append_to_string(&message, "|");
    append_to_string(&message, user->uuid);
    append_to_string(&message, "\a\n");
    if (response_server(socket, message) == ERROR)
        return ERROR;
    return OK;
}

static int copy_in_user_list(server_data_t *server, user_t *user)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (server == NULL || user == NULL || new_user == NULL)
        return ERROR;
    new_user->username = strdup(user->username);
    new_user->uuid = strdup(user->uuid);
    new_user->teams = user->teams;
    new_user->personnal_messages = user->personnal_messages;
    if (new_user->username == NULL || new_user->uuid == NULL)
        return ERROR;
    LIST_INSERT_HEAD(&server->users, new_user, entries);
    return OK;
}

static int user_connection(server_data_t *server, client_server_t *client)
{
    user_t user;

    if (server == NULL || client == NULL)
        return ERROR;
    if (already_exist(server, client, client->command->params->user_name)
    == OK) {
        if (login_response(client->socket, client->user) == ERROR)
            return ERROR;
        return OK;
    }
    if (user_initialisation(&user, client->command->params->user_name)
    == ERROR)
        return ERROR;
    client->user = &user;
    client->is_logged = true;
    if (copy_in_user_list(server, client->user) == ERROR)
        return ERROR;
    if (login_response(client->socket, client->user) == ERROR)
        return ERROR;
    return OK;
}

int login(server_data_t *server, client_server_t *client)
{
    user_t user;

    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == true) {
        write(client->socket, "401 Already logged\a\n", 21);
        return OK;
    }
    if (user_connection(server, client) == ERROR)
        return ERROR;
    server_event_user_logged_in(client->user->uuid);
    return OK;
}

int logout(server_data_t *server, client_server_t *client)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false) {
        write(client->socket, "500, You are not logged in\a\n", 29);
        return OK;
    }
    client->is_logged = false;
    write(client->socket, "200 Logout Succed\n", 19);
    return OK;
}
