/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** load_data
*/

#include "server.h"

static void load_users(server_data_t *server_data)
{
    int file = open("saves/users.txt", O_RDONLY);
    user_t *tmp = malloc(sizeof(user_t));

    if (file == -1) {
        free(tmp);
        return;
    }
    while (read(file, tmp, sizeof(user_t)) > 0) {
        TAILQ_INIT(&tmp->personnal_messages);
        TAILQ_INSERT_HEAD(&server_data->users, tmp, entries);
        server_data->users.tqh_first->user_connected = 0;
        tmp = malloc(sizeof(user_t));
    }
    free(tmp);
}

static void load_teams(server_data_t *server_data)
{
    int file = open("saves/teams.txt", O_RDONLY);
    team_t *tmp = malloc(sizeof(team_t));

    if (file == -1) {
        free(tmp);
        return;
    }
    while (read(file, tmp, sizeof(team_t)) > 0) {
        TAILQ_INIT(&tmp->channels);
        TAILQ_INIT(&tmp->users);
        TAILQ_INSERT_HEAD(&server_data->teams, tmp, entries);
        tmp = malloc(sizeof(team_t));
    }
    free(tmp);
}

void load_data(server_data_t *server_data)
{
    load_users(server_data);
    load_teams(server_data);
}
