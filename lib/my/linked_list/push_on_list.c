/*
** EPITECH PROJECT, 2023
** SBMLParser
** File description:
** push_on_list
*/

#include <unistd.h>

#include "proto_lib.h"
#include "linked_list.h"

static int move_in_list(list_t **list_dest, list_t *tmp)
{
    list_t *tmp_2 = NULL;

    if (!tmp)
        return -1;
    if ((*list_dest) == NULL){
        (*list_dest) = tmp;
        tmp->next = NULL;
        return 0;
    }
    tmp_2 = (*list_dest);
    tmp->next = tmp_2;
    (*list_dest) = tmp;
    return 0;
}

int push_on_list(list_t **list_src, list_t **list_dest)
{
    int list_len = 0;
    list_t *tmp_1 = (*list_src);
    list_t *tmp_2 = NULL;

    if (!(*list_src))
        return -1;
    list_len = my_list_len((*list_src));
    if (list_len == -1)
        return -1;
    if (list_len < 2){
        if (move_in_list(list_dest, tmp_1) == -1)
            return 0;
        (*list_src) = NULL;
    } else {
        tmp_2 = (*list_src)->next;
        if (move_in_list(list_dest, tmp_1) == -1)
            return -1;
        (*list_src) = tmp_2;
    }
    return 0;
}
