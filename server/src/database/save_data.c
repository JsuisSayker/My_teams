/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** save_data
*/

#include "server.h"

static void save_users(server_data_t *server_data, int file)
{
    user_t *tmp = server_data->users.tqh_first;

    while (tmp) {
        write(file, "user", 4);
        write(file, tmp, sizeof(user_t));
        tmp = tmp->entries.tqe_next;
    }
}

static void save_channels(channel_t *channel, int file)
{
    channel_t *tmp = channel;

    while (tmp) {
        write(file, "chan", 4);
        write(file, tmp, sizeof(channel_t));
        tmp = tmp->entries.tqe_next;
    }
}

static void save_teams(server_data_t *server_data, int file)
{
    team_t *tmp = server_data->teams.tqh_first;

    while (tmp) {
        write(file, "team", 4);
        write(file, tmp, sizeof(team_t));
        save_channels(tmp->channels.tqh_first, file);
        tmp = tmp->entries.tqe_next;
    }
}

void save_data(server_data_t *server_data)
{
    int file = open("saves/data.txt", O_CREAT | O_TRUNC | O_WRONLY | O_APPEND,
        00777);

    if (file == -1)
        return;
    save_users(server_data, file);
    save_teams(server_data, file);
    close(file);
}
