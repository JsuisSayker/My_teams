/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** save_data
*/

#include "server.h"

static void save_users(server_data_t *server_data)
{
    user_t *tmp = server_data->users.lh_first;
    int file = open("saves/users.txt", O_CREAT | O_WRONLY);

    if (file == -1)
        return;
    LIST_FOREACH(tmp, &server_data->users, entries) {
        write(file, tmp, sizeof(user_t));
    }
    close(file);
}

void save_data(server_data_t *server_data)
{
    save_users(server_data);
}
