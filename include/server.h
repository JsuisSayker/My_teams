/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <sys/queue.h>
    #include <netinet/in.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include "proto_lib.h"
    #include "client.h"
    #include "macro.h"
    #include "logging_server.h"

typedef struct message_s {
    char *message;
    char *sender_uuid;
    LIST_ENTRY(message_s) entries;
} message_t;

typedef struct thread_s {
    LIST_HEAD(, message_t) messages;
    LIST_ENTRY(thread_s) entries;
} thread_t;

typedef struct channel_s {
    char *channel_uuid;
    char *channel_name;
    LIST_ENTRY(channel_s) entries;
    LIST_HEAD(, message_t) messages;
    LIST_HEAD(, user_t) users;
    LIST_HEAD(, thread_t) threads;
} channel_t;

typedef struct personnal_message_s {
    char *message;
    char *sender_uuid;
    char *receiver_uuid;
    LIST_ENTRY(personnal_message_s) entries;
} personnal_message_t;

typedef struct team_s {
    char *team_uuid;
    char *team_name;
    LIST_ENTRY(team_s) entries;
    LIST_HEAD(, channel_t) channels;
    LIST_HEAD(, user_t) users;
} team_t;

typedef struct user_s {
    char *username;
    char *uuid;
    char *description;
    LIST_ENTRY(user_s) entries;
    LIST_HEAD(, team_t) teams;
    LIST_HEAD(, personnal_message_t) personnal_messages;
} user_t;

typedef struct client_server_s {
    int socket;
    user_t *user;
    bool is_logged;
    char *user_input;
    user_input_t *command;
    LIST_ENTRY(client_server_s) entries;
} client_server_t;

typedef enum {
    TEAMS,
    CHANNELS,
    THREADS,
    NONE
} context_t;

typedef struct server_data_s {
    int server_socket;
    fd_set current_sockets;
    fd_set ready_sockets;
    struct sockaddr_in server_address;
    LIST_HEAD(, user_s) users;
    LIST_HEAD(, client_server_s) clients;
    LIST_HEAD(, team_s) teams;
    int client_is_deco;
} server_data_t;

struct function_tab_s {
    char *str;
    int (*flags)(server_data_t *server, client_server_t *client);
};

struct parse_command_s {
    char *command;
    user_input_t *(*func)(char **user_input);
};

int display_help(void);
int launch_server(char *const *const av);
void free_server_data(server_data_t *server_data);
int create_server_socket(char *const *const av, server_data_t *data);
int loop_check_select_client(server_data_t *server_data);
char *read_client(server_data_t *data, int client_socket);
int accept_client(server_data_t *data);
int response_server(int socket, char *message);

int find_command(server_data_t *server, client_server_t *client);
int login(server_data_t *server, client_server_t *client);
int logout(server_data_t *server, client_server_t *client);
int user(server_data_t *server, client_server_t *client);
void check_command(server_data_t *server_data, client_server_t *client);
void free_user_input(user_input_t *user_input);
user_input_t *init_user_input_structure(void);
user_input_t *login_parser(char **user_input);

/* toolbox */
int append_to_string(char **str, char *to_append);
int user_initialisation(user_t *user, char *name);
char *generate_uuid(void);

#endif /* !SERVER_H_ */
