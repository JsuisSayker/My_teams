/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "client.h"

int main(int ac, char const *const *av)
{
    if (check_arguments(ac, av) == KO)
        return ERROR;
    return OK;
}
