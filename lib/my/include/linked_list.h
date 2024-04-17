/*
** EPITECH PROJECT, 2023
** LIB
** File description:
** linked_list
*/

#ifndef LINKED_LIST_H_
    #define LINKED_LIST_H_

typedef struct list_s {
    char *username;
    char *description;
    struct list_s *next;
} list_t;

#endif /* !LINKED_LIST_H_ */
