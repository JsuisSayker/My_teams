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
    #include <fcntl.h>
    #include <string.h>
    #include "proto_lib.h"
    #include "client.h"
    #include "macro.h"
    #include "logging_server.h"

typedef struct message_s {
    char message[MAX_BODY_LENGTH];
    char sender_uuid[UUID_LENGTH];
    char timestamp[TIME_LENGTH];
    TAILQ_ENTRY(message_s) entries;
} message_t;

typedef struct thread_s {
    char timestamp[TIME_LENGTH];
    char thread_uuid[UUID_LENGTH];
    char title[MAX_NAME_LENGTH];
    char message[MAX_BODY_LENGTH];
    char sender_uuid[UUID_LENGTH];
    TAILQ_HEAD(, message_s) messages;
    TAILQ_ENTRY(thread_s) entries;
} thread_t;

typedef struct channel_s {
    char channel_uuid[UUID_LENGTH];
    char channel_name[MAX_NAME_LENGTH];
    char channel_description[MAX_DESCRIPTION_LENGTH];
    TAILQ_ENTRY(channel_s) entries;
    TAILQ_HEAD(, thread_s) threads;
} channel_t;

typedef struct personnal_message_s {
    char message[MAX_BODY_LENGTH];
    char sender_uuid[UUID_LENGTH];
    char receiver_uuid[UUID_LENGTH];
    char time[TIME_LENGTH];
    bool is_read;
    TAILQ_ENTRY(personnal_message_s) entries;
} personnal_message_t;

typedef struct team_s {
    char team_uuid[UUID_LENGTH];
    char team_name[MAX_NAME_LENGTH];
    char team_description[MAX_DESCRIPTION_LENGTH];
    TAILQ_ENTRY(team_s) entries;
    TAILQ_HEAD(, channel_s) channels;
    TAILQ_HEAD(, user_s) users;
} team_t;

typedef struct user_s {
    char username[MAX_NAME_LENGTH];
    char uuid[UUID_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int user_connected;
    TAILQ_ENTRY(user_s) entries;
    TAILQ_HEAD(, personnal_message_s) personnal_messages;
} user_t;

typedef struct contex_s {
    team_t *team;
    channel_t *channel;
    thread_t *thread;
} context_t;

typedef struct client_server_s {
    user_input_t *command;
    user_t *user;
    context_t context;
    int socket;
    bool is_logged;
    char *user_input;
    TAILQ_ENTRY(client_server_s) entries;
} client_server_t;

typedef struct server_data_s {
    int server_socket;
    fd_set current_sockets;
    fd_set ready_sockets;
    struct sockaddr_in server_address;
    TAILQ_HEAD(, user_s) users;
    TAILQ_HEAD(, client_server_s) clients;
    TAILQ_HEAD(, team_s) teams;
    int client_is_deco;
} server_data_t;

struct function_tab_s {
    char *str;
    int (*flags)(server_data_t *server, client_server_t *client);
};

struct parse_command_s {
    char *command;
    user_input_t *(*func)(char **user_input, client_server_t *client);
};

int display_help(void);
int launch_server(char *const *const av);
void free_server_data(server_data_t *server_data);
int create_server_socket(char *const *const av, server_data_t *data);
char *read_client(server_data_t *data, int client_socket);
int accept_client(server_data_t *data);
int server_response(int socket, char *message);


/* command */
int server_message_command(server_data_t *server, client_server_t *client);
int server_send_command(server_data_t *server, client_server_t *client);
int find_command(server_data_t *server, client_server_t *client);
int login(server_data_t *server, client_server_t *client);
int logout(server_data_t *server, client_server_t *client);
int users(server_data_t *server, client_server_t *client);
int user(server_data_t *server, client_server_t *client);

/* parer */
void free_user_input(user_input_t *user_input);
int loop_check_select_client(server_data_t *server_data);
int check_command(server_data_t *server_data, client_server_t *client);
user_input_t *init_user_input_structure(void);
user_input_t *create_parser(char **user_input, client_server_t *client);
user_input_t *help_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *info_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *list_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *login_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *logout_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *send_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *subscribe_parser(char **user_input,
    UNUSED client_server_t *client);
user_input_t *subscribed_parser(char **user_input,
    UNUSED client_server_t *client);
user_input_t *unsubscribe_parser(char **user_input,
    UNUSED client_server_t *client);
user_input_t *use_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *user_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *users_parser(char **user_input, UNUSED client_server_t *client);
user_input_t *messages_parser(char **user_input,
    UNUSED client_server_t *client);
void free_client(client_server_t *client);
void save_data(server_data_t *server_data);
void load_data(server_data_t *server_data);
int use(server_data_t *server, client_server_t *client);
int create(server_data_t *server, client_server_t *client);
int create_new_team_response(server_data_t *server,
    client_server_t *client, team_t *new_team);
int create_new_channel_response(server_data_t *server,
    client_server_t *client, channel_t *new_channel);
int create_new_thread_response(server_data_t *server,
    client_server_t *client, thread_t *new_thread);
int create_new_reply_response(server_data_t *server,
    client_server_t *client, message_t *new_message);
void free_clients(server_data_t *server_data);
void free_users(server_data_t *server_data);
void free_teams(server_data_t *server_data);
int subscribe(server_data_t *server, client_server_t *client);
int is_subscribed(user_t *user, team_t *team);
int unsubscribe(server_data_t *server_data, client_server_t *client);

/* toolbox */
client_server_t *client_is_connected(server_data_t *server, user_t *user);
personnal_message_t *create_personnal_message(char *message, char *sender_uuid,
    char *receiver_uuid, int socket);
int user_initialisation(user_t **new_user, char *name, int socket);
user_t *get_user_by_uuid(server_data_t *server, char *uuid);
bool user_is_exist(server_data_t *server, char *user_uuid);
char **tab_append_str_at_end(char **tab, char *str);
int append_to_string(char **str, char *to_append);
int get_time(char (*dest)[TIME_LENGTH]);
char *generate_uuid(void);
team_t *get_team_by_uuid(team_t *teams, char *uuid);
void send_user_not_found(client_server_t *client);

#endif /* !SERVER_H_ */
