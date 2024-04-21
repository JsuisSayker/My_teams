/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** load_data
*/

#include "server.h"

static void load_user(server_data_t *server_data, int file)
{
    user_t *user = calloc(sizeof(user_t), 1);

    if (user == NULL)
        return;
    if (read(file, user, sizeof(user_t)) <= 0) {
        free(user);
        return;
    }
    TAILQ_INIT(&user->personnal_messages);
    TAILQ_INSERT_HEAD(&server_data->users, user, entries);
    server_data->users.tqh_first->user_connected = 0;
}

static void load_team(server_data_t *server_data, int file)
{
    team_t *team = calloc(sizeof(team_t), 1);

    if (team == NULL)
        return;
    if (read(file, team, sizeof(team_t)) <= 0) {
        free(team);
        return;
    }
    TAILQ_INIT(&team->users);
    TAILQ_INIT(&team->channels);
    TAILQ_INSERT_HEAD(&server_data->teams, team, entries);
}

void load_data(server_data_t *server_data)
{
    char buffer[BUFSIZ];
    int file = open("saves/data.txt", O_RDONLY, 00777);

    if (file == -1)
        return;
    while (read(file, buffer, 4) > 0) {
        buffer[4] = '\0';
        if (strcmp(buffer, "user") == 0)
            load_user(server_data, file);
        if (strcmp(buffer, "team") == 0)
            load_team(server_data, file);
    }
    close(file);
}
