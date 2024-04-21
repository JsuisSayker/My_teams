/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** print_error_message
*/

#include <unistd.h>
#include <string.h>

void print_error_message(char **command, int start)
{
    for (int i = start; command[i]; i += 1) {
        write(1, command[i], strlen(command[i]));
        write(1, " ", 1);
    }
    write(1, "\n", 1);
}
