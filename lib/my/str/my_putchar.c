/*
** EPITECH PROJECT, 2022
** fek
** File description:
** f;e;lz
*/

#include <unistd.h>

int my_putchar(char c)
{
    if (write(1, &c, 1) == -1)
        return -1;
    return 0;
}
