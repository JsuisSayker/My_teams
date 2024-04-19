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
        LIST_INSERT_HEAD(&server_data->users, tmp, entries);
        tmp = malloc(sizeof(user_t));
    }
    free(tmp);
}

void load_data(server_data_t *server_data)
{
    load_users(server_data);
}
