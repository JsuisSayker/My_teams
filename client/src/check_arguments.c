/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** check_arguments
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "macro.h"

static int help_message(void)
{
    if (write(1, "USAGE: ./myteams_cli ip port\
    ip\tis the server ip address on which the server socket listens\n\
    port\tis the port number on which the server socket listens\n", 154) == -1)
        return KO;
    return OK;
}

static int check_ip(char const *ip)
{
    int ip_len = 0;

    if (ip == NULL)
        return KO;
    for (int i = 0; ip[i] != '\0'; i++){
        if (ip[i] == '.')
            ip_len++;
        if (ip[i] != '.' && ip[i] < '0' || ip[i] > '9')
            return KO;
    }
    if (ip_len != 3)
        return KO;
    return OK;
}

int check_arguments(int ac, char const *const *av)
{
    if (ac < 2)
        return KO;
    if (strcmp(av[1], "-help") == 0)
        if (help_message() == KO)
            return KO;
    if (ac < 3)
        return KO;
    if (check_ip(av[1]) == KO)
        return KO;
    if (check_port(av[2]) == KO)
        return KO;
    return OK;
}
