/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** init
*/

#include "server.h"

user_input_t *init_user_input_structure(void)
{
    user_input_t *user_input = malloc(sizeof(user_input_t));

    if (user_input == NULL)
        return NULL;
    user_input->command = NULL;
    user_input->params = malloc(sizeof(param_t));
    if (user_input->params == NULL)
        return NULL;
    user_input->params->user_name = NULL;
    user_input->params->user_uuid = NULL;
    user_input->params->team_name = NULL;
    user_input->params->team_uuid = NULL;
    user_input->params->team_description = NULL;
    user_input->params->channel_name = NULL;
    user_input->params->channel_uuid = NULL;
    user_input->params->channel_description = NULL;
    user_input->params->thread_title = NULL;
    user_input->params->thread_uuid = NULL;
    user_input->params->thread_body = NULL;
    return user_input;
}
