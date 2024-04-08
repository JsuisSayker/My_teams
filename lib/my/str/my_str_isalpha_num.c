/*
** EPITECH PROJECT, 2023
** lib
** File description:
** my_str_isalpha_num
*/

#include <unistd.h>

int my_str_isalpha_num(char const *str, int i)
{
    if (str == NULL)
        return -1;
    if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
    (str[i] < '0' || str[i] > '9'))
        return -1;
    return 0;
}

int my_all_str_isalpha_num(char const *str)
{
    if (str == NULL)
        return -1;
    for (int i = 0; str[i] != '\0'; i ++){
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') &&
        (str[i] < '0' || str[i] > '9'))
            return -1;
    }
    return 0;
}
