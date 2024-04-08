/*
** EPITECH PROJECT, 2023
** SBMLParser
** File description:
** my_letter_isalpha
*/

#include <unistd.h>

int my_letter_isalpha(char letter)
{
    if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))
            return -1;
    return 0;
}
