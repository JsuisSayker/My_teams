/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** comman
*/

#include "server.h"

static const struct parse_command_s PARSE_COMMAND[] = {
    {"/login", &login_parser},
    {"/logout", &logout_parser},
    {"/users", &users_parser},
    {"/user", &user_parser},
    {"/send", &send_parser},
    {"/messages", &messages_parser},
    {"/subscribe", &subscribe_parser},
    {"/subscribed", &subscribed_parser},
    {"/unsubscribe", &unsubscribe_parser},
    {"/use", &use_parser},
    {"/create", &create_parser},
    {"/list", &list_parser},
    {"/info", &info_parser},
    {"/help", &help_parser},
    {NULL, NULL}
};

void check_command(server_data_t *server_data, client_server_t *client)
{
    char **user_input = NULL;

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
                client->command = PARSE_COMMAND[i].func(user_input, client);
        }
        if (client->command == NULL)
            write(client->socket, "214 bad command, type /help to show commands\a\n", 47);
        else {
            printf("command = %s\n", client->command->command);
            find_command(server_data, client);
            free_user_input(client->command);
            client->command = NULL;
        }
        free_tab(user_input);
        free(client->user_input);
        client->user_input = NULL;
    }
}
