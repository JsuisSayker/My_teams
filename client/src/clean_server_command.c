/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** clean_server_command
*/

#include <stdio.h>

static void clean_server_message(char *message)
{
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] == '\n' || message[i] == '\a')
            message[i] = '\0';
    }
}

void clean_server_command(char **command)
{
    for (int i = 0; command[i] != NULL; i += 1) {
        clean_server_message(command[i]);
    }
}
