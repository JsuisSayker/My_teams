/*
** EPITECH PROJECT, 2023
** B-CPE-200-BDX-2-1-lemin-marc.mendia
** File description:
** my_list_len
*/

#include <unistd.h>
#include "linked_list.h"

int my_list_len(list_t *list)
{
    int count = 0;
    list_t *list_tmp = list;

    for (; list_tmp != NULL; list_tmp = list_tmp->next)
        count ++;
    return count;
}
