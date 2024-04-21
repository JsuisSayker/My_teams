/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list
*/

#include "server.h"

static int list_all_reply(server_data_t *server, client_server_t *client)
{
    char *message = NULL;
    message_t *reply = client->context.thread->messages.tqh_first;

    append_to_string(&message, "200|/list|");
    TAILQ_FOREACH(reply, &client->context.thread->messages, entries) {
        append_to_string(&message, client->context.thread->thread_uuid);
        append_to_string(&message, "|");
        append_to_string(&message, reply->sender_uuid);
        append_to_string(&message, "|");
        append_to_string(&message, reply->timestamp);
        append_to_string(&message, "|");
        append_to_string(&message, reply->message);
        if (reply->entries.tqe_next != NULL)
            append_to_string(&message, "|");
    }
    append_to_string(&message, "\a\n");
    server_response(client->socket, message);
    free(message);
    return OK;
}

static int list_all_channel(server_data_t *server, client_server_t *client)
{
    char *message = NULL;
    channel_t *channel = client->context.team->channels.tqh_first;

    append_to_string(&message, "200|/list|");
    TAILQ_FOREACH(channel, &client->context.team->channels, entries) {
        append_to_string(&message, channel->channel_uuid);
        append_to_string(&message, "|");
        append_to_string(&message, channel->channel_name);
        append_to_string(&message, "|");
        append_to_string(&message, channel->channel_description);
        if (channel->entries.tqe_next != NULL)
            append_to_string(&message, "|");
    }
    append_to_string(&message, "\a\n");
    server_response(client->socket, message);
    free(message);
    return OK;
}

static int list_thread(char **message, thread_t *thread)
{
    append_to_string(message, thread->thread_uuid);
    append_to_string(message, "|");
    append_to_string(message, thread->sender_uuid);
    append_to_string(message, "|");
    append_to_string(message, thread->timestamp);
    append_to_string(message, "|");
    append_to_string(message, thread->title);
    append_to_string(message, "|");
    append_to_string(message, thread->message);
    if (thread->entries.tqe_next != NULL)
        append_to_string(message, "|");
    return OK;
}

static int list_all_threads(server_data_t *server, client_server_t *client)
{
    char *message = NULL;
    thread_t *thread = client->context.channel->threads.tqh_first;

    append_to_string(&message, "200|/list|");
    TAILQ_FOREACH(thread, &client->context.channel->threads, entries) {
        if (list_thread(&message, thread) == ERROR)
            return ERROR;
    }
    append_to_string(&message, "\a\n");
    server_response(client->socket, message);
    free(message);
    return OK;
}

static int list_all_teams(server_data_t *server, client_server_t *client)
{
    char *message = NULL;
    team_t *team = server->teams.tqh_first;

    append_to_string(&message, "200|/list|");
    TAILQ_FOREACH(team, &server->teams, entries) {
        append_to_string(&message, team->team_uuid);
        append_to_string(&message, "|");
        append_to_string(&message, team->team_name);
        append_to_string(&message, "|");
        append_to_string(&message, team->team_description);
        if (team->entries.tqe_next != NULL)
            append_to_string(&message, "|");
    }
    append_to_string(&message, "\a\n");
    server_response(client->socket, message);
    free(message);
    return OK;
}

int server_list_command(server_data_t *server, client_server_t *client)
{
    if (client->is_logged == false) {
        write(client->socket, "401|/list|You are not logged in\a\n", 34);
        return OK;
    }
    if (client->context.team != NULL && is_subscribed(client->user,
        client->context.team) == ERROR) {
        write(client->socket,
            "401|/list|You are not subscribed to this team\a\n", 48);
        return OK;
    }
    if (client->context.thread != NULL)
        return list_all_reply(server, client);
    if (client->context.channel != NULL)
        return list_all_threads(server, client);
    if (client->context.team != NULL)
        return list_all_channel(server, client);
    if (client->context.team == NULL)
        return list_all_teams(server, client);
    return OK;
}
