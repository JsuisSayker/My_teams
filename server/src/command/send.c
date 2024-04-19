/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** send
*/

#include "server.h"

static int send_command_response(client_server_t *client,
personnal_message_t *message)
{
    char *response = NULL;

    if (message == NULL || client == NULL)
        return ERROR;
    append_to_string(&response, "200|/send|");
    append_to_string(&response, client->user->username);
    append_to_string(&response, "|");
    append_to_string(&response, message->message);
    append_to_string(&response, "\a\n");
    if (server_response(client->socket, response) == ERROR)
        return ERROR;
    return OK;
}

static int message_user(client_server_t *client, user_t *receiver)
{
    personnal_message_t *message = malloc(sizeof(personnal_message_t));

    if (message == NULL || client == NULL || receiver == NULL)
        return ERROR;
    if (strcpy(message->message, client->command->params->message_body) == NULL)
        return ERROR;
    if (strcpy(message->sender_uuid, client->user->uuid) == NULL)
        return ERROR;
    if (strcpy(message->receiver_uuid, receiver->uuid) == NULL)
        return ERROR;
    TAILQ_INSERT_HEAD(&receiver->personnal_messages,
        copy_message(message), entries);
    TAILQ_INSERT_HEAD(&client->user->personnal_messages,
        copy_message(message), entries);
    if (send_command_response(client, message) == ERROR)
        return ERROR;
    return OK;
}

int server_send_command(server_data_t *server, client_server_t *client)
{
    user_t *user = NULL;

    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500|Your not logged\a\n\0", 23);
        return OK;
    }
    user = get_user_by_uuid(server, client->command->params->user_uuid);
    if (user == NULL){
        write(client->socket, "500|User don't exist\a\n\0", 24);
        return OK;
    }
    if (message_user(client, user) == ERROR)
        return ERROR;
    return OK;
}