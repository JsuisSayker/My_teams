/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** comman
*/

#include "server.h"

static const struct parse_command_s PARSE_COMMAND[] = {
    {"/login", &login_parser},
    // {"/logout", &logout_parser},
    // {"/users", &users_parser},
    // {"/user", &user_parser},
    // {"/send", &send_parser},
    // {"/messages", &messages_parser},
    // {"/subscribe", &subscribe_parser},
    // {"/subscribed", &subscribed_parser},
    // {"/unsubscribe", &unsubscribe_parser},
    // {"/use", &use_parser},
    // {"/create", &create_parser},
    // {"/list", &list_parser},
    // {"/info", &info_parser},
    // {"/help", &help_parser},
    {NULL, NULL}
};

void check_command(server_data_t *server_data, client_server_t *client)
{
    char **user_input = NULL;
    user_input_t *input_parse = NULL;

    if (client->user_input[strlen(client->user_input) - 1] ==
    '\n' && client->user_input[strlen(client->user_input) - 2]
    == '\a') {
        client->user_input[strlen(client->user_input) - 2] =
        '\0';
        user_input = my_splitstr(client->user_input, ' ');
        if (user_input == NULL)
            return;
        for (int i = 0; PARSE_COMMAND[i].command != NULL; i++) {
            if (strcmp(PARSE_COMMAND[i].command, user_input[0]) == 0)
                input_parse = PARSE_COMMAND[i].func(user_input);
        }
        if (input_parse == NULL)
            write(client->socket, "214 bad command, type /help to show commands\a\n", 47);
        write(client->socket, "/login toto|69ET\a\n", 19);
        free_tab(user_input);
        free(client->user_input);
        free_user_input(input_parse);
        client->user_input = NULL;
    }
}
