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

static print_tab(char **tab)
{
    for (int i = 0; tab[i]; i++) {
        printf("tab[%d] = [%s]\n", i, tab[i]);
    }
}

static int get_command(char *message, char *user_message, client_t *client)
{
    char **command = spliter_by_sep(message, " |");
    char **user_command = spliter_by_sep(user_message, " |");
    print_tab(command);
    print_tab(user_command);

    for (int i = 0; COMMANDS[i].name; i++) {
        if (strcmp(command[0], COMMANDS[i].name) == 0) {
            COMMANDS[i].func(message, command, client);
            return OK;
        }
    }
    return OK;
}

int user_input_event(char *message, char *user_message, client_t *client)
{
    if (message == NULL)
        return ERROR;
    return get_command(message, user_message, client);
}
