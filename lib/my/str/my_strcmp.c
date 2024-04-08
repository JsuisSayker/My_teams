/*
** EPITECH PROJECT, 2022
** Lib
** File description:
** reproduit le compartment de strcmp
*/

#include <unistd.h>

int my_strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return -1;
    for (int count = 0; s1[count] != '\0' || s2[count] != '\0'; count ++){
        if (s1[count] != s2[count])
            return -1;
    }
    return 0;
}
