/*
** EPITECH PROJECT, 2022
** my_strncmp
** File description:
** a Faire
*/

#include <unistd.h>

int my_strncmp(char const *s1, char const *s2, int n)
{
    int count = 0;

    if (!s1 || !s2)
        return -1;
    for (count = 0; (s1[count] != '\0' || s2[count] != '\0') && count < n;
    count ++) {
        if (s1[count] != s2[count])
            return -1;
    }
    if (n > count || n < count)
        return 1;
    return 0;
}
