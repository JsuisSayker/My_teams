/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

int main(int ac, char const *const *av)
{
    if (!av)
        return KO;
    if (check_arguments(ac, av) == ERROR)
        return KO;
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return display_help();
    if (is_good_number(av[2]) == true)
        return start_client_connection(av[1], atoi(av[2]));
    else {
        if (write(1, "Invalid port number\n", 20) == ERROR)
            return KO;
        return KO;
    }
    return OK;
}
