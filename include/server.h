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
    #include <netinet/in.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "macro.h"

typedef struct server_data_s {
    int server_socket;
    struct sockaddr_in server_address;
} server_data_t;

int display_help(void);
int launch_server(char *const *const av);
void free_server_data(server_data_t *server_data);
int create_server_socket(char *const *const av, server_data_t *data);

#endif /* !SERVER_H_ */
