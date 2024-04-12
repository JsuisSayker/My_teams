/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include "macro.h"
    #include "../libs/myteams/logging_client.h"
    #include <stdbool.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <signal.h>
    #include <string.h>

typedef struct client_s {
    bool is_logged;
    char *uuid;
    char *user_name;
    int socket_fd;
} client_t;

struct command_s {
    char *name;
    int (*func)(char *message, char **command,client_t *client);
};

int check_arguments(int ac, char const *const *av);
int display_help(void);
bool is_good_number(const char *str);
int start_client_connection(const char *ip, int port);
void client_logout(client_t *client, char *command);
char **spliter_by_sep(char *str, char *separator);
int user_input_event(char *message, client_t *client);

// commands
int login_command(char *message, char **command, client_t *client);
int users_command(char *message, char **command, client_t *client);
int logout_command(char *message, char **command, client_t *client);
int user_command(char *message, char **command, client_t *client);
int send_command(char *message, char **command, client_t *client);
int messages_command(char *message, char **command, client_t *client);
int subscribe_command(char *message, char **command, client_t *client);
int subscribed_command(char *message, char **command, client_t *client);
int unsubscribe_command(char *message, char **command, client_t *client);
int list_command(char *message, char **command, client_t *client);

#endif /* !CLIENT_H_ */