/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** handle_server_code
*/

#include "client.h"

int handle_server_code_ter(char **command)
{
    switch (atoi(command[0])) {
        case 600:
            client_error_unknown_team(command[3]);
            return KO;
        case 601:
            client_error_unknown_channel(command[3]);
            return KO;
        case 602:
            client_error_unknown_thread(command[3]);
            return KO;
        default:
            return OK;
    }
}

int handle_server_code_sub(char **command)
{
    switch (atoi(command[0])) {
        case 401:
            client_error_unauthorized();
            return KO;
        case 403:
            client_error_already_exist();
            return KO;
        case 404:
            client_error_unknown_user(command[2]);
            return KO;
        case 500:
            print_error_message(command, 2);
            return KO;
        default:
            return handle_server_code_ter(command);
    }
}

int handle_server_code(char **command)
{
    switch (atoi(command[0])) {
        case 200:
            break;
        case 204:
            print_error_message(command, 1);
            return KO;
        case 214:
            print_error_message(command, 1);
            return KO;
        default:
            return handle_server_code_sub(command);
    }
}
