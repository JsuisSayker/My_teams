/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** message
*/

#include "server.h"

static int message_command_response(list_t *list, int socket)
{
    char *message = NULL;

    append_to_string(&message, "200|/users|");
    if (list == NULL)
        return ERROR;
    for (list_t *tmp = list; tmp != NULL; tmp = tmp->next) {
        append_to_string(&message, tmp->message);
        append_to_string(&message, "|");
        append_to_string(&message, tmp->receiver_uuid);
        append_to_string(&message, "|");
        append_to_string(&message, tmp->sender_uuid);
        if (tmp->next != NULL)
            append_to_string(&message, "|");
    }
    append_to_string(&message, "\a\n");
    if (server_response(socket, message) == ERROR)
        return ERROR;
    free(message);
    return OK;
}

static int get_list(list_t **list, server_data_t *server,
    client_server_t *client)
{
    personnal_message_t *tmp;

    if (client == NULL || list == NULL)
        return ERROR;
    tmp = client->user->personnal_messages.tqh_first;
    TAILQ_FOREACH(tmp, &client->user->personnal_messages, entries) {
        if ((strcmp(tmp->receiver_uuid,
                client->command->params->user_uuid) == 0) ||
            (strcmp(tmp->sender_uuid,
                client->command->params->user_uuid) == 0)){
        (*list) = add_node_message_in_list((*list), tmp->message,
            tmp->sender_uuid, tmp->receiver_uuid);
        }
    }
    if ((*list) == NULL){
        write(client->socket, "500, No message found\n\r", 22);
        return OK;
    }
    return OK;
}

int server_message_command(server_data_t *server, client_server_t *client)
{
    list_t *list = NULL;

    if (client == NULL || server == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\a\n\0", 24);
        return OK;
    }
    if (user_is_exist(server, client->command->params->user_uuid) == false){
        write(client->socket, "500, User not found\a\n\0", 23);
        return OK;
    }
    if (get_list(&list, server, client) == ERROR)
        return ERROR;
    if (list == NULL)
        return OK;
    if (message_command_response(list, client->socket) == ERROR)
        return ERROR;
    free_message_list(list);
    return OK;
}