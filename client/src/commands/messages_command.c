/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** messages_command
*/

#include "client.h"
#include <time.h>


static time_t convert_string_to_time_t(const char *time_string,
    const char *format)
{
    struct tm time_struct = {0};
    time_t time = 0;

    if (strptime(time_string, format, &time_struct) == NULL) {
        printf("Failed to parse time string.\n");
        return ERROR;
    }
    time = mktime(&time_struct);
    if (time == ERROR) {
        printf("Failed to convert struct tm to time_t.\n");
        return ERROR;
    }
    return time;
}

int messages_command(char *message, char **command, client_t *client)
{
    time_t time = 0;

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
