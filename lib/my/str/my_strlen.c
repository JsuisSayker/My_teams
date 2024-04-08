/*
** EPITECH PROJECT, 2022
** my_strlen
** File description:
** task03
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return -1;
    for (i = 0; str[i] != '\0'; i += 1);
    return i;
}
