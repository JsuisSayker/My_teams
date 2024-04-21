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

    if (file == -1)
        return;
    while (read(file, tmp, sizeof(user_t)) > 0) {
        TAILQ_INIT(&tmp->personnal_messages);
        TAILQ_INSERT_HEAD(&server_data->users, tmp, entries);
        server_data->users.tqh_first->user_connected = 0;
        tmp = malloc(sizeof(user_t));
    }
    free(tmp);
}

void load_data(server_data_t *server_data)
{
    load_users(server_data);
}
