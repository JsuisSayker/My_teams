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

// static char **parse_user_input(char *user_input)
// {
//     char *token = NULL;
//     char **parsed_input = NULL;

//     if (user_input == NULL || user_input[0] != '/')
//         return NULL;
//     token = strtok(user_input, " \t");
//     while (token != NULL) {
//         printf("token: %s\n", token);
//         token = strtok(NULL, " \t\"");
//     }
//     return parsed_input;
// }

static void parse_and_launch_command(server_data_t *server_data,
    client_server_t *client)
{
    char **user_input = NULL;

    client->user_input[strlen(client->user_input) - 2] = '\0';
    user_input = my_splitstr(client->user_input, ' ');
    // parse_user_input(client->user_input);
    if (user_input == NULL)
        return;
    for (int i = 0; PARSE_COMMAND[i].command != NULL; i++) {
        if (strcmp(PARSE_COMMAND[i].command, user_input[0]) == 0)
            client->command = PARSE_COMMAND[i].func(user_input, client);
    }
    if (client->command == NULL)
        write(client->socket, "214 bad command, type /help\a\n", 30);
    else {
        find_command(server_data, client);
        free_user_input(client->command);
        client->command = NULL;
    }
    free_tab(user_input);
    free(client->user_input);
    client->user_input = NULL;
}

void check_command(server_data_t *server_data, client_server_t *client)
{
    if (client->user_input[strlen(client->user_input) - 1] ==
    '\n' && client->user_input[strlen(client->user_input) - 2]
    == '\a')
        parse_and_launch_command(server_data, client);
}
