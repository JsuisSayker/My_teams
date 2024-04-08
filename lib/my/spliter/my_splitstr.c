/*
** EPITECH PROJECT, 2023
** Lib
** File description:
** my_splitstr
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int count_word(char const *str, int separator)
{
    int nbr_word = 1;

    if (str == NULL)
        return -1;
    for (int i = 0; str[i] != '\0'; i += 1){
        if (str[i] == separator)
            nbr_word += 1;
    }
    return nbr_word;
}

static int add_value_in_tab(char **tab_str, int *index, char const *str_copy,
    int separator)
{
    int i = 0;

    if (tab_str == NULL || index == NULL || str_copy == NULL)
        return -1;
    for (; str_copy[*index] != '\0'
    && str_copy[*index] != separator; *index += 1){
        (*tab_str)[i] = str_copy[*index];
        i += 1;
    }
    (*tab_str)[i] = '\0';
    return 0;
}

static int malloc_str(char **tab_str, int index, char const *str_copy,
    int separator)
{
    int len = 0;

    if (tab_str == NULL || str_copy == NULL)
        return -1;
    for (; str_copy[index] != '\0'
    && str_copy[index] != separator; index += 1)
        len += 1;
    (*tab_str) = malloc(sizeof(char) * (len + 1));
    if ((*tab_str) == NULL)
        return -1;
    return 0;
}

static int my_split_sub(char **tab, int *index, char const *str, int separator)
{
    if (tab == NULL || index == NULL || str == NULL)
        return -1;
    if (malloc_str(tab, *index, str, separator) == -1)
        return -1;
    if (add_value_in_tab(tab, index, str, separator) == -1)
        return -1;
    return 0;
}

char **my_splitstr(char const *str, int separator)
{
    char **tab = NULL;
    int len_tab = 0;
    int index = 0;

    if (str == NULL)
        return NULL;
    len_tab = count_word(str, separator);
    if (len_tab == -1)
        return NULL;
    tab = malloc(sizeof(char *) * (len_tab + 1));
    if (tab == NULL)
        return NULL;
    tab[len_tab] = NULL;
    for (int i = 0; i < len_tab; i += 1){
        if (my_split_sub(&tab[i], &index, str, separator) == -1)
            return NULL;
        index += 1;
    }
    return tab;
}
