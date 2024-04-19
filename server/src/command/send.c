/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** send
*/

#include "server.h"

static int message_user(server_data_t *server, client_server_t *client)
{
    personnal_message_t *message = malloc(sizeof(personnal_message_t));
    user_t *user_receve;

    if (message == NULL || client == NULL || server == NULL)
        return ERROR;
    user_receve = get_user_by_uuid(server, client->command->params->user_uuid);
    if (user_receve == NULL)
        return ERROR;
    strcpy(message->message, client->command->params->message_body);
    strcpy(message->sender_uuid, client->user->uuid);
    strcpy(message->receiver_uuid, client->command->params->user_uuid);
        return ERROR;
    return OK;
}

int server_send_command(server_data_t *server, client_server_t *client)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\a\n\0", 24);
        return ERROR;
    }
    if (user_is_exist(server,
        client->command->params->user_uuid) == false){
        write(client->socket, "500, Don't exist\a\n\0", 20);
        return ERROR;
    }
    if (message_user(server, client) == ERROR)
        return ERROR;
    return OK;
}
