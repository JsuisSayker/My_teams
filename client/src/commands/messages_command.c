/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** messages_command
*/

#include "client.h"

int messages_command(char *message, char **command, client_t *client)
{
    time_t time = 0;

    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    for (int i = 2; command[i] != NULL; i += 3) {
        time = convert_string_to_time_t(command[i + 1],
            "%a %b %d %H:%M:%S %Y");
        if (time == ERROR)
            return ERROR;
        client_private_message_print_messages(command[i], time,
            command[i + 2]);
    }
    return OK;
}
