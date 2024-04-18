/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login_logout
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

static int login_response(user_t *user, int socket)
{
    char *response = NULL;

    if (user == NULL)
        return ERROR;
    append_to_string(&response, "200 /login ");
    append_to_string(&response, user->username);
    append_to_string(&response, "|");
    append_to_string(&response, user->uuid);
    append_to_string(&response, "\a\n");
    server_response(socket, response);
    return OK;
}

static int user_connection(server_data_t *server, client_server_t *client)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (new_user == NULL)
        return ERROR;
    new_user->username = strdup(client->command->params->user_name);
    new_user->uuid = generate_uuid();
    new_user->description = NULL;
    new_user->entries.le_next = NULL;
    new_user->entries.le_prev = NULL;
    if (server->users.lh_first == NULL)
        LIST_INSERT_HEAD(&server->users, new_user, entries);
    else
        add_user_on_server_database(server, new_user);
    client->user = new_user;
    if (login_response(new_user, client->socket) == ERROR)
        return ERROR;
    return OK;
}

static int already_exist(server_data_t *server, client_server_t *client,
    char *username)
{
    user_t *tmp;

    if (server == NULL || client == NULL || username == NULL)
        return ERROR;
    tmp = server->users.lh_first;
    while (tmp) {
        if (strcmp(tmp->username, username) == 0) {
            client->user = tmp;
            client->is_logged = true;
            return OK;
        }
        tmp = tmp->entries.le_next;
    }
    return ERROR;
}

int login(server_data_t *server, client_server_t *client)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == true) {
        write(client->socket, "401 Already logged\a\n\0", 22);
        return OK;
    }
    if (already_exist(server, client, client->command->params->user_name)
    == OK) {
        if (login_response(client->user, client->socket) == ERROR)
            return ERROR;
        return OK;
    }
    if (user_connection(server, client) == ERROR)
        return ERROR;
    user_t *tmp = server->users.lh_first;
    LIST_FOREACH(tmp, &server->users, entries) {
        printf("username: %s\n", tmp->username);
        printf("uuid: %s\n", tmp->uuid);
    }
    return OK;
}

int logout(server_data_t *server, client_server_t *client)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\a\n\0", 24);
        return OK;
    }
    client->is_logged = false;
    write(client->socket, "200 /logout Succed\a\n\0", 21);
    return OK;
}
