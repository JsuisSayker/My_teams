/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** user_input_event
*/

#include "client.h"

static const struct command_s COMMANDS[] = {
    {"/login", &login_command},
    {"/logout", &logout_command},
    {"/users", &users_command},
    {"/user", &user_command},
    {"/send", &send_command},
    {"/messages", &messages_command},
    {"/subscribe", &subscribe_command},
    {"/subscribed", &subscribed_command},
    {"/unsubscribe", &unsubscribe_command},
    {"/use", &use_command},
    // {"/create", &create_command},
    {"/list", &list_command},
    // {"/info", &info_command},
    // {"/help", &help_command},
    {NULL, NULL}
};

// static void print_tab(char **tab)
// {
//     for (int i = 0; tab[i]; i += 1) {
//         printf("tab[%d] = [%s]\n", i, tab[i]);
//     }
// }

static int get_command(char *message, client_t *client)
{
    char **command = spliter_by_sep(message, " |");

    clean_server_command(command);
    for (int i = 0; COMMANDS[i].name; i += 1) {
        if (strcmp(command[1], COMMANDS[i].name) == 0) {
            COMMANDS[i].func(message, command, client);
            free(message);
            free_tab(command);
            return OK;
        }
    }
    free_tab(command);
    free(message);
    return OK;
}

int user_input_event(char *message, client_t *client)
{
    if (message == NULL)
        return ERROR;
    return get_command(message, client);
}
