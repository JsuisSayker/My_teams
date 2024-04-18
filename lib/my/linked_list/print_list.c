/*
** EPITECH PROJECT, 2023
** B-CPE-200-BDX-2-1-lemin-marc.mendia
** File description:
** print_list
*/

#include <unistd.h>
#include <stdio.h>

#include "proto_lib.h"
#include "linked_list.h"

int print_node(list_user_t *node)
{
    if (!node)
        return -1;
    printf("%s\n", node->username);
    printf("%s\n", node->description);
    return 0;
}

int print_list(list_user_t *list)
{
    if (!list)
        return -1;
    for (list_user_t *list_user_tmp = list; list_user_tmp != NULL; list_user_tmp = list_user_tmp->next){
        if (printf("\n[---------{%s}---------]\n", list_user_tmp->username) < 0)
            return -1;
        if (printf("\n[---------{%s}---------]\n", list_user_tmp->description) < 0)
            return -1;
        print_node(list_user_tmp);
        if (printf("[---------{end}--------]\n\n") < 0)
            return -1;
    }
    return 0;
}
