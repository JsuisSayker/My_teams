/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** help_command
*/

#include "client.h"
#include <unistd.h>
#include <fcntl.h>


int help_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    for (int i = 2; command[i] != NULL; i += 1) {
        write(1, command[i], strlen(command[i]));
        write(1, "\n", 1);
    }
    return OK;
}
