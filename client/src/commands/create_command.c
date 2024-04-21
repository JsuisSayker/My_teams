/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** create_command
*/

#include "client.h"

static int create_command_sub(char **command)
{
    if (strcmp(command[2], "thread") == 0) {
        client_event_thread_created(command[3], command[4],
            convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
            command[6], command[7]);
        client_print_thread_created(command[3], command[4],
            convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
            command[6], command[7]);
        return OK;
    }
    if (strcmp(command[2], "reply") == 0) {
        client_print_reply_created(command[3], command[4],
            convert_string_to_time_t(command[5], "%a %b %d %H:%M:%S %Y"),
            command[6]);
        client_event_thread_reply_received(command[7], command[3],
            command[4], command[6]);
        return OK;
    }
    return OK;
}

int create_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    if (strcmp(command[2], "team") == 0) {
        client_event_team_created(command[3], command[4], command[5]);
        client_print_team_created(command[3], command[4], command[5]);
        return OK;
    }
    if (strcmp(command[2], "channel") == 0) {
        client_event_channel_created(command[3], command[4], command[5]);
        client_print_channel_created(command[3], command[4], command[5]);
        return OK;
    }
    create_command_sub(command);
    return OK;
}
