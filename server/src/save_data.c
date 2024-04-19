/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** save_data
*/

#include "server.h"

static void save_users(server_data_t *server_data)
{
    user_t *tmp = server_data->users.tqh_first;
    int file = open("saves/users.txt", O_CREAT | O_WRONLY);

    if (file == -1)
        return;
    while (tmp) {
        write(file, tmp, sizeof(user_t));
        tmp = tmp->entries.tqe_next;
    }
    close(file);
}

void save_data(server_data_t *server_data)
{
    save_users(server_data);
}
