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
    if (tmp != NULL && strcmp(tmp->username, name) == 0){
        client->user = tmp;
        client->is_logged = true;
        return OK;
    }
    return ERROR;
}

static int message_and_response(char *command, client_server_t *client,
    user_t *user)
{
    char *message = NULL;

    if (command == NULL || user == NULL)
        return ERROR;
    append_to_string(&message, "200 ");
    append_to_string(&message, command);
    append_to_string(&message, " ");
    append_to_string(&message, user->username);
    append_to_string(&message, "|");
    append_to_string(&message, user->uuid);
    append_to_string(&message, "\a\n");
    if (server_response(client->socket, message) == ERROR)
        return ERROR;
    return OK;
}


static int user_connection(server_data_t *server, client_server_t *client)
{
    user_t user;

    if (server == NULL || client == NULL)
        return ERROR;
    if (user_initialisation(&user, client->command->params->user_name)
    == ERROR)
        return ERROR;
    client->user = &user;
    client->is_logged = true;
    if (add_user_on_server_database(server, client->user) == ERROR)
        return ERROR;
    if (message_and_response("/login", client, client->user) == ERROR)
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
    if (already_exist(server, client, client->command->params->user_name)
    == OK) {
        if (message_and_response("/login", client, client->user) == ERROR)
            return ERROR;
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
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\n", 22);
        return OK;
    }
    client->is_logged = false;
    write(client->socket, "200 Logout Succed\n", 19);
    return OK;
}
