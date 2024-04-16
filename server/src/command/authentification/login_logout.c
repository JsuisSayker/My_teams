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
        return ERROR;
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
        write(client->socket, "200 Logged in\n", 15);
        return OK;
    }
    if (user_initialisation(&user, client->command[1]) == ERROR)
        return ERROR;
    client->user = &user;
    write(client->socket, "200 Logged in\n", 15);
    return OK;
}

int login(server_data_t *server, client_t *client)
{
    user_t user;

    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == true) {
        write(client->socket, "401 Already logged in\n", 23);
        return OK;
    }
    if (client->command[1] == NULL) {
        write(client->socket, "500 Missing username\n", 22);
        return OK;
    }
    if (user_initialisation(server, client) == ERROR)
        return ERROR;
    client->user = &user;
    return OK;
}

int logout(server_data_t *server, client_t *client)
{
    if (client->is_logged == false) {
        write(client->socket, "500, You need to be logged to have acces to \
this command\n", 58);
        return OK;
    }
    client->is_logged = false;
    write(client->socket, "200 Logout Succed\n", 19);
    return OK;
}
