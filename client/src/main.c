/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "proto.h"

int main(int ac, char const *const *av)
{
    if (check_arguments(ac, av) == KO)
        return ERROR;
    return OK;
}
