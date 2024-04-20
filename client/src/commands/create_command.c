/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** create_command
*/

#include "client.h"

static void create_thread_context(char **command)
{
    client_event_thread_created(command[3], command[4],
        convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
        command[6], command[7]);
}

int create_command(char *message, char **command, client_t *client)
{
    if (strcmp(command[2], "team") == 0) {
        client_event_team_created(command[3], command[4], command[5]);
        return OK;
    }
    if (strcmp(command[2], "channel") == 0) {
        client_event_channel_created(command[3], command[4], command[5]);
        return OK;
    }
    if (strcmp(command[2], "thread") == 0) {
        create_thread_context(command);
        return OK;
    }
    if (strcmp(command[2], "reply") == 0) {
        client_print_reply_created(command[3], command[4],
            convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
            command[6]);
        return OK;
    }
    return OK;
}
