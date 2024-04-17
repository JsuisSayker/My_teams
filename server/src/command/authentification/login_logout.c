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
            client->user->username = strdup(tmp->username);
            client->user->uuid = strdup(tmp->uuid);
            client->is_logged = true;
            return OK;
        }
    }
    return ERROR;
}

static int message_and_response(char *command, client_server_t *client,
    user_t *user)
{
    int len_message;
    char *message = NULL;

    if (command == NULL || user == NULL)
        return ERROR;
    len_message =
        strlen(command) + strlen(user->username) + strlen(user->uuid);
    message = malloc(sizeof(char) * len_message + 5);
    strcpy(message, command);
    strcat(message, " ");
    strcat(message, user->username);
    strcat(message, "|");
    strcat(message, user->uuid);
    strcat(message, "\a\n\0");
    if (response_server(client->socket, message) == ERROR)
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
    if (user_initialisation(&user, client->user_input->params->user_name)
    == ERROR)
        return ERROR;
    client->user = &user;
    client->is_logged = true;
    if (copy_in_user_list(server, client->user) == ERROR)
        return ERROR;
    if (message_and_response("login", client, client->user) == ERROR)
        return ERROR;
    return OK;
}

int login(server_data_t *server, client_server_t *client)
{
    user_t user;

    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == true) {
        write(client->socket, "401 Already logged in\n", 23);
        return OK;
    }
    if (client->user_input->params->user_name == NULL) {
        write(client->socket, "500 Missing username\n", 22);
        return OK;
    }
    if (already_exist(server, client, client->user_input->params->user_name)
    == OK) {
        if (message_and_response("login", client, client->user) == ERROR)
            return ERROR;
        return OK;
    }
    if (user_connection(server, client) == ERROR)
        return ERROR;
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
