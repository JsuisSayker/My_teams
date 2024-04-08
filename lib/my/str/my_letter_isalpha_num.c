/*
** EPITECH PROJECT, 2023
** SBMLParser
** File description:
** my_letter_isalpha
*/

#include <unistd.h>

int my_letter_isalpha_num(char letter)
{
    if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z') &&
    (letter < '0' || letter > '9'))
        return -1;
    return 0;
}
