/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** login
*/

#include "server.h"

user_input_t *login_parser(char **user_input)
{
    printf("login parser\n");
    user_input_t *user_input_parsed = init_user_input_structure();

    if (user_input == NULL || user_input_parsed == NULL)
        return NULL;
    if (user_input[0] == NULL)
        return NULL;
    if (user_input[1] == NULL)
        return NULL;
    user_input_parsed->command = strdup(user_input[0]);
    user_input_parsed->params->user_name = strdup(user_input[1]);
    return user_input_parsed;
}
