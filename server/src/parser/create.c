/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** create
*/

#include "server.h"

user_input_t *create_parser(char **user_input, client_server_t *client)
{
    user_input_t *user_input_parsed = init_user_input_structure();

    if (user_input == NULL || user_input_parsed == NULL ||
    user_input[0] == NULL) {
        free_user_input(user_input_parsed);
        return NULL;
    }
    user_input_parsed->command = strdup(user_input[0]);
    if (client->context == NONE) {
        if (user_input[1] != NULL && user_input[2] != NULL &&
        user_input[3] == NULL) {
            user_input_parsed->command = strdup(user_input[0]);
            user_input_parsed->params->team_name = strdup(user_input[1]);
            user_input_parsed->params->team_description = strdup(
                user_input[2]);
        } else {
            free_user_input(user_input_parsed);
            return NULL;
        }
    } else if (client->context == TEAMS) {
        if (user_input[1] != NULL && user_input[2] != NULL &&
        user_input[3] == NULL) {
            user_input_parsed->command = strdup(user_input[0]);
            user_input_parsed->params->channel_name = strdup(user_input[1]);
            user_input_parsed->params->channel_description = strdup(
                user_input[2]);
        } else {
            free_user_input(user_input_parsed);
            return NULL;
        }
    } else if (client->context == CHANNELS) {
        if (user_input[1] != NULL && user_input[2] != NULL &&
        user_input[3] == NULL) {
            user_input_parsed->command = strdup(user_input[0]);
            user_input_parsed->params->thread_title = strdup(user_input[1]);
            user_input_parsed->params->thread_body = strdup(user_input[2]);
        } else {
            free_user_input(user_input_parsed);
            return NULL;
        }
    } else if (client->context == THREADS) {
        if (user_input[1] != NULL && user_input[2] == NULL) {
            user_input_parsed->command = strdup(user_input[0]);
            user_input_parsed->params->comment_body = strdup(user_input[1]);
        } else {
            free_user_input(user_input_parsed);
            return NULL;
        }
    }
    return user_input_parsed;
}
