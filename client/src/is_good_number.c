/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** is_good_port
*/

#include <string.h>
#include <stdbool.h>
#include "macro.h"

bool is_good_number (const char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}
