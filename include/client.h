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
    #include <stdlib.h>
    #include "proto_lib.h"


typedef struct param_s {
    char *user_name;
    char *user_uuid;
    char *team_uuid;
    char *team_name;
    char *team_description;
    char *channel_uuid;
    char *channel_name;
    char *channel_description;
    char *thread_uuid;
    char *thread_title;
    char *thread_body;
    char *message_body;
    char *comment_body;
} param_t;

typedef struct user_input_s {
    char *command;
    param_t *params;
} user_input_t;

typedef struct client_s {
    bool is_logged;
    char *uuid;
    char *user_name;
    int socket_fd;
    user_input_t *user_input;
} client_t;

struct command_s {
    char *name;
    int (*func)(char *message, char **command, client_t *client);
};

// sub functions
int check_arguments(int ac, char const *const *av);
int display_help(void);
bool is_good_number(const char *str);
int start_client_connection(const char *ip, int port);
void client_logout(client_t *client, char **command, char *message);
char **spliter_by_sep(char *str, char *separator);
int user_input_event(char *message, client_t *client);
void send_client_message(client_t *client);

// toolbox
void clean_server_command(char **command);
void free_client_struct(client_t *client, fd_set *readfds, fd_set *otherfds);
char *read_server_message(client_t *client);
void receive_server_message(client_t *client);
time_t convert_string_to_time_t(const char *time_string, const char *format);

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
int use_command(char *message, char **command, client_t *client);
int help_command(char *message, char **command, client_t *client);
int create_command(char *message, char **command, client_t *client);
int info_command(char *message, char **command, client_t *client);

#endif /* !CLIENT_H_ */
