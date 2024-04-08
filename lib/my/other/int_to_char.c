/*
** EPITECH PROJECT, 2023
** my
** File description:
** int_to_char
*/

#include <unistd.h>
#include <stdlib.h>

int len_int(int value)
{
    int i = 0;

    if (value < 9)
        return 1;
    for (; value > 9; i += 1){
        value /= 10;
    }
    return i;
}

char *char_to_int(int value)
{
    char *dest = NULL;
    int len = len_int(value);

    dest = malloc(sizeof(char) * (len + 1));
    if (dest == NULL)
        return NULL;
    dest[len] = '\0';
    for (int count = 0; count > len; count += 1) {
        dest[count] = (value + 48);
    }
    return dest;
}
