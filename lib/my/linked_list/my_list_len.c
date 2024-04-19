/*
** EPITECH PROJECT, 2023
** B-CPE-200-BDX-2-1-lemin-marc.mendia
** File description:
** my_list_len
*/

#include <unistd.h>
#include "linked_list.h"

int my_list_len(list_user_t *list)
{
    int count = 0;
    list_user_t *list_user_tmp = list;

    for (; list_user_tmp != NULL; list_user_tmp = list_user_tmp->next)
        count ++;
    return count;
}
