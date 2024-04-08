/*
** EPITECH PROJECT, 2023
** B-MUL-100-BDX-1-1-myradar-marc.mendia
** File description:
** char_to_int
*/

#include "proto_lib.h"
#include <unistd.h>

static int is_neg(char c, int *sing, int *i)
{
    if (sing == NULL || i == NULL)
        return -1;
    if (c == '-'){
        *sing = -1;
        *i += 1;
    }
    return 0;
}

int char_to_int(char const *str)
{
    long int nbr = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return -1;
    if (is_neg(str[i], &sign, &i) == -1)
        return -1;
    for (; str[i] != '\0'; i += 1){
        if (str[i] < '0' || str[i] > '9'){
            return -1;
        }
        nbr = (nbr * 10) + (str[i] - '0');
    }
    nbr *= sign;
    if (nbr > 2147483647 || nbr < -2147483648)
        return -1;
    i = (int)(nbr);
    return i;
}
