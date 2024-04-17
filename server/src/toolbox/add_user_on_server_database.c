/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** add_user_on_server_database
*/

#include "server.h"

// static int copy_in_user_list(server_data_t *server, user_t *new_user)
// {
//     user_t *tmp = NULL;

//     if (server == NULL || new_user == NULL)
//         return ERROR;
//     if (server->users.lh_first == NULL) {
//         printf("[FIRST]\n\n");
//         LIST_INSERT_HEAD(&server->users, new_user, entries);
//         return OK;
//     }
//     tmp = server->users.lh_first;
//     LIST_FOREACH(tmp, &server->users, entries) {
//         if (tmp->entries.le_next == NULL) {
//             LIST_INSERT_AFTER(tmp, new_user, entries);
//             break;
//         }
//     }
//     return OK;
// }

int add_user_on_server_database(server_data_t *server, user_t *user)
{
    user_t *new_user = malloc(sizeof(user_t));

    if (server == NULL || user == NULL || new_user == NULL)
        return ERROR;
    new_user->username = strdup(user->username);
    new_user->uuid = strdup(user->uuid);
    new_user->teams = user->teams;
    new_user->personnal_messages = user->personnal_messages;
    if (new_user->username == NULL || new_user->uuid == NULL)
        return ERROR;
    // if (copy_in_user_list(server, new_user) == ERROR)
    //     return ERROR;
    LIST_INSERT_HEAD(&server->users, new_user, entries);
    return OK;
}
