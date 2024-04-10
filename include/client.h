/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include "macro.h"
    #include <stdbool.h>

int check_arguments(int ac, char const *const *av);
int display_help(void);
bool is_good_number (const char *str);

#endif /* !CLIENT_H_ */
