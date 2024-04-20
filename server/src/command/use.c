/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** use
*/

#include "server.h"

static team_t *get_team(server_data_t *server, char *team_uuid)
{
    team_t *tmp;

    if (server == NULL || team_uuid == NULL)
        return NULL;
    tmp = server->teams.tqh_first;
    while (tmp) {
        if (strcmp(tmp->team_uuid, team_uuid) == 0)
            return tmp;
        tmp = tmp->entries.tqe_next;
    }
    return NULL;
}

static channel_t *get_channel(team_t *team, char *channel_uuid)
{
    channel_t *tmp;

    if (team == NULL || channel_uuid == NULL)
        return NULL;
    tmp = team->channels.tqh_first;
    while (tmp) {
        if (strcmp(tmp->channel_uuid, channel_uuid) == 0)
            return tmp;
        tmp = tmp->entries.tqe_next;
    }
    return NULL;
}

static thread_t *get_thread(channel_t *channel, char *thread_uuid)
{
    thread_t *tmp;

    if (channel == NULL || thread_uuid == NULL)
        return NULL;
    tmp = channel->threads.tqh_first;
    while (tmp) {
        if (strcmp(tmp->thread_uuid, thread_uuid) == 0)
            return tmp;
        tmp = tmp->entries.tqe_next;
    }
    return NULL;
}

static int use_sub(server_data_t *server, client_server_t *client)
{
    if (client->command->params->channel_uuid != NULL) {
        client->context.channel = get_channel(client->context.team,
        client->command->params->channel_uuid);
        if (client->context.channel == NULL) {
            write(client->socket, "404, Channel not found\a\n\0", 27);
            return ERROR;
        }
    }
    if (client->command->params->thread_uuid != NULL) {
        client->context.thread = get_thread(client->context.channel,
        client->command->params->thread_uuid);
        if (client->context.thread == NULL) {
            write(client->socket, "404, Thread not found\a\n\0", 26);
            return ERROR;
        }
    }
    return OK;
}

int use(server_data_t *server, client_server_t *client)
{
    if (server == NULL || client == NULL)
        return ERROR;
    if (client->is_logged == false){
        write(client->socket, "500, Your not logged\a\n\0", 24);
        return ERROR;
    }
    if (client->command->params->team_uuid != NULL) {
        client->context.team = get_team(server,
        client->command->params->team_uuid);
        if (client->context.team == NULL) {
            write(client->socket, "404, Team not found\a\n\0", 24);
            return ERROR;
        }
    }
    return use_sub(server, client);
}
