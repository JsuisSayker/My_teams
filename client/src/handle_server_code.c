/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** handle_server_code
*/

#include "client.h"

int handle_server_code(char **command)
{
    switch (atoi(command[0])) {
        case 200:
            break;
        case 500:
            print_error_message(command, 2);
            return KO;
        case 401:
            client_error_unauthorized();
            return KO;
        case 404:
            client_error_unknown_user(command[2]);
            return KO;
        default:
            return KO;
    }
}
