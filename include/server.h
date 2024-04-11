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
    #include "macro.h"

typedef struct message_s {
    char *message;
    char *sender_uuid;
    LIST_ENTRY(message_s) entries;
} message_t;

typedef struct channel_s {
    char *channel_uuid;
    char *channel_name;
    LIST_ENTRY(channel_s) entries;
    //  *messages;
    // queue *users;
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
    channel_t *channels;
    // user_t *users;
} team_t;

typedef struct user_s {
    int socket;
    bool is_logged;
    char *username;
    char *uuid;
    char *command;
    LIST_ENTRY(user_s) entries;
    personnal_message_t *teams;
    team_t *teams;
} user_t;

typedef struct server_data_s {
    int server_socket;
    fd_set current_sockets;
    fd_set ready_sockets;
    struct sockaddr_in server_address;
} server_data_t;

struct function_tab_s {
    char *str;
    int (*flags)(server_data_t *server, user_t *user);
};

int display_help(void);
int launch_server(char *const *const av);
void free_server_data(server_data_t *server_data);
int create_server_socket(char *const *const av, server_data_t *data);

#endif /* !SERVER_H_ */
