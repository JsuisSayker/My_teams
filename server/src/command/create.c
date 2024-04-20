/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** create
*/

#include "server.h"

static int is_subscribed(user_t *user, team_t *team)
{
    user_t *tmp;

    if (user == NULL || team == NULL)
        return ERROR;
    tmp = team->users.tqh_first;
    while (tmp) {
        if (strcmp(tmp->uuid, user->uuid) == 0)
            return OK;
        tmp = tmp->entries.tqe_next;
    }
    return ERROR;
}

static int create_new_reply_response(server_data_t *server,
    client_server_t *client, message_t *new_message)
{
    char *response = NULL;

    append_to_string(&response, "200|/create|reply|");
    append_to_string(&response, client->context.thread->thread_uuid);
    append_to_string(&response, "|");
    append_to_string(&response, client->user->uuid);
    append_to_string(&response, "|");
    append_to_string(&response, new_message->timestamp);
    append_to_string(&response, "|");
    append_to_string(&response, client->command->params->comment_body);
    append_to_string(&response, "\a\n");
    write(client->socket, response, strlen(response));
    free(response);
    return OK;
}

static int create_new_thread_response(server_data_t *server,
    client_server_t *client, thread_t *new_thread)
{
    char *response = NULL;

    append_to_string(&response, "200|/create|thread|");
    append_to_string(&response, new_thread->thread_uuid);
    append_to_string(&response, "|");
    append_to_string(&response, client->user->uuid);
    append_to_string(&response, "|");
    append_to_string(&response, new_thread->timestamp);
    append_to_string(&response, "|");
    append_to_string(&response, new_thread->title);
    append_to_string(&response, "|");
    append_to_string(&response, new_thread->message);
    append_to_string(&response, "\a\n");
    write(client->socket, response, strlen(response));
    free(response);
    return OK;
}

static int create_new_channel_response(server_data_t *server,
    client_server_t *client, channel_t *new_channel)
{
    char *response = NULL;

    append_to_string(&response, "200|/create|channel|");
    append_to_string(&response, new_channel->channel_uuid);
    append_to_string(&response, "|");
    append_to_string(&response, new_channel->channel_name);
    append_to_string(&response, "|");
    append_to_string(&response, new_channel->channel_description);
    append_to_string(&response, "\a\n");
    write(client->socket, response, strlen(response));
    free(response);
    return OK;
}

static int create_new_team_response(server_data_t *server,
    client_server_t *client, team_t *new_team)
{
    char *response = NULL;

    append_to_string(&response, "200|/create|team|");
    append_to_string(&response, new_team->team_uuid);
    append_to_string(&response, "|");
    append_to_string(&response, new_team->team_name);
    append_to_string(&response, "|");
    append_to_string(&response, new_team->team_description);
    append_to_string(&response, "\a\n");
    write(client->socket, response, strlen(response));
    free(response);
    return OK;
}

static int create_new_reply(server_data_t *server, client_server_t *client)
{
    thread_t *thread = client->context.thread;
    message_t *new_message = calloc(sizeof(message_t), 1);

    if (new_message == NULL)
        return ERROR;
    if (is_subscribed(client->user, client->context.team) == ERROR) {
        write(client->socket,
            "400, You are not subscribed to this team\a\n", 43);
        free(new_message);
        return ERROR;
    }
    strcpy(new_message->message, client->command->params->comment_body);
    strcpy(new_message->sender_uuid, client->user->uuid);
    get_time(&(new_message)->timestamp);
    TAILQ_INSERT_HEAD(&thread->messages, new_message, entries);
    return create_new_reply_response(server, client, new_message);
}

static int create_new_thread(server_data_t *server, client_server_t *client)
{
    char *uuid = generate_uuid();
    channel_t *channel = client->context.channel;
    thread_t *new_thread = calloc(sizeof(thread_t), 1);

    if (new_thread == NULL)
        return ERROR;
    if (is_subscribed(client->user, client->context.team) == ERROR) {
        write(client->socket,
            "400, You are not subscribed to this team\a\n", 43);
        return ERROR;
    }
    strcpy(new_thread->thread_uuid, uuid);
    strcpy(new_thread->title, client->command->params->thread_title);
    strcpy(new_thread->message, client->command->params->comment_body);
    strcpy(new_thread->sender_uuid, client->user->uuid);
    get_time(&(new_thread)->timestamp);
    TAILQ_INSERT_HEAD(&channel->threads, new_thread, entries);
    client->context.thread = new_thread;
    free(uuid);
    return create_new_thread_response(server, client, new_thread);
}

static int create_new_channel(server_data_t *server, client_server_t *client)
{
    char *uuid = generate_uuid();
    team_t *team = client->context.team;
    channel_t *new_channel = calloc(sizeof(channel_t), 1);

    if (new_channel == NULL)
        return ERROR;
    if (is_subscribed(client->user, client->context.team) == ERROR) {
        write(client->socket,
            "400, You are not subscribed to this team\a\n", 43);
        return ERROR;
    }
    strcpy(new_channel->channel_uuid, uuid);
    strcpy(new_channel->channel_name, client->command->params->channel_name);
    strcpy(new_channel->channel_description,
        client->command->params->channel_description);
    TAILQ_INSERT_HEAD(&team->channels, new_channel, entries);
    client->context.channel = new_channel;
    free(uuid);
    return create_new_channel_response(server, client, new_channel);
}

static int create_new_team(server_data_t *server, client_server_t *client)
{
    char *uuid = generate_uuid();
    team_t *new_team = calloc(sizeof(team_t), 1);

    if (new_team == NULL)
        return ERROR;
    strcpy(new_team->team_uuid, uuid);
    strcpy(new_team->team_name, client->command->params->team_name);
    strcpy(new_team->team_description,
        client->command->params->team_description);
    TAILQ_INSERT_HEAD(&server->teams, new_team, entries);
    client->context.team = new_team;
    free(uuid);
    return create_new_team_response(server, client, new_team);
}

int create(server_data_t *server, client_server_t *client)
{
    if (client->is_logged == false) {
        write(client->socket, "500, You are not logged in\n", 28);
        return OK;
    }
    if (client->context.thread != NULL)
        return create_new_reply(server, client);
    if (client->context.channel != NULL)
        return create_new_thread(server, client);
    if (client->context.team != NULL)
        return create_new_channel(server, client);
    if (client->context.team == NULL)
        return create_new_team(server, client);
    return OK;
}
