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

int print_node(list_t *node)
{
    if (!node)
        return -1;
    printf("%s\n", node->str);
    return 0;
}

int print_list(list_t *list)
{
    if (!list)
        return -1;
    for (list_t *list_tmp = list; list_tmp != NULL; list_tmp = list_tmp->next){
        if (printf("\n[---------{%s}---------]\n", list_tmp->str) < 0)
            return -1;
        print_node(list_tmp);
        if (printf("[---------{end}--------]\n\n") < 0)
            return -1;
    }
    return 0;
}
