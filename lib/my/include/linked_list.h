/*
** EPITECH PROJECT, 2023
** LIB
** File description:
** linked_list
*/

#ifndef LINKED_LIST_H_
    #define LINKED_LIST_H_

typedef struct list_user_s {
    char *username;
    char *description;
    char *uuid;
    struct list_user_s *next;
} list_user_t;

#endif /* !LINKED_LIST_H_ */
