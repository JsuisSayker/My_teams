/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** free
*/

#include "server.h"

void free_client(client_server_t *client)
{
    if (client) {
        if (client->socket)
            close(client->socket);
        if (client->user_input)
            free(client->user_input);
        if (client->command)
            free_user_input(client->command);
        free(client);
    }
}

static void free_clients(server_data_t *server_data)
{
    client_server_t *client = NULL;
    client_server_t *tmp = NULL;

    if (!server_data)
        return;
    while (!LIST_EMPTY(&server_data->clients)) {
        client = LIST_FIRST(&server_data->clients);
        LIST_REMOVE(client, entries);
        free_client(client);
    }
}

static void free_user(user_t *user)
{
    if (user) {
        if (user->username)
            free(user->username);
        if (user->uuid)
            free(user->uuid);
        if (user->description)
            free(user->description);
        free(user);
    }
}

static void free_users(server_data_t *server_data)
{
    user_t *user = NULL;
    user_t *tmp = NULL;

    if (!server_data)
        return;
    while (!LIST_EMPTY(&server_data->users)) {
        user = LIST_FIRST(&server_data->users);
        LIST_REMOVE(user, entries);
        free_user(user);
    }
}

void free_server_data(server_data_t *server_data)
{
    if (!server_data)
        return;
    if (server_data->server_socket != -1)
        close(server_data->server_socket);
    if (server_data->clients.lh_first)
        free_clients(server_data);
    if (server_data->users.lh_first)
        free_users(server_data);
    free(server_data);
}

void free_user_input_sub(user_input_t *user_input)
{
    if (user_input->params->team_description)
        free(user_input->params->team_description);
    if (user_input->params->channel_name)
        free(user_input->params->channel_name);
    if (user_input->params->channel_uuid)
        free(user_input->params->channel_uuid);
    if (user_input->params->channel_description)
        free(user_input->params->channel_description);
    if (user_input->params->thread_title)
        free(user_input->params->thread_title);
    if (user_input->params->thread_uuid)
        free(user_input->params->thread_uuid);
    if (user_input->params->thread_body)
        free(user_input->params->thread_body);
    if (user_input->params->message_body)
        free(user_input->params->message_body);
    if (user_input->params->comment_body)
        free(user_input->params->comment_body);
}

void free_user_input(user_input_t *user_input)
{
    if (!user_input)
        return;
    if (user_input->command)
        free(user_input->command);
    if (user_input->params) {
        if (user_input->params->user_name)
            free(user_input->params->user_name);
        if (user_input->params->user_uuid)
            free(user_input->params->user_uuid);
        if (user_input->params->team_name)
            free(user_input->params->team_name);
        if (user_input->params->team_uuid)
            free(user_input->params->team_uuid);
        free_user_input_sub(user_input);
        free(user_input->params);
    }
    free(user_input);
}
