/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login_logout
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

static int user_initialisation(user_t *user, char *name)
{
    if (name == NULL || user == NULL)
        return KO;
    user->username = strdup(name);
    user->uuid = generate_uuid();
    user->teams = NULL;
    user->personnal_messages = NULL;
    return OK;
}

static int user_connection(server_data_t *server, client_t *client)
{
    user_t user;
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->user != NULL){
        client->is_logged = true;
        dprintf(client->socket, "200 Logged in\n");
        return OK;
    }
    user_initialisation(&user, client->command[1]);
}

int login(server_data_t *server, client_t *client)
{
    user_t user;
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == true) {
        dprintf(client->socket, "401 Already logged in\n");
        return KO;
    }
    if (client->command[1] == NULL) {
        dprintf(client->socket, "500 Missing username\n");
        return KO;
    }
    if (client->user != NULL){
        client->is_logged = true;
        dprintf(client->socket, "200 Logged in\n");
        return OK;
    }
    user_initialisation(&user, client->command[1]);
    client->user = &user;
    dprintf(client->socket, "200 Logged in\n");
    return OK;
}

int logout(server_data_t *server, user_t *user)
{

}