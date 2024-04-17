/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** users_function
*/

#include "server.h"

int user(server_data_t *server, client_server_t *client)
{
    if (client == NULL || server == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\n\r", 23);
        return OK;
    }
    return OK;
}
