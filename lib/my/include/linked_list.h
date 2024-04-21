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
    char *uuid;
    char *is_connected;
    struct list_user_s *next;
} list_user_t;

typedef struct list_s {
    char *message;
    char *sender_uuid;
    char *time_stamp;
    struct list_s *next;
} list_t;

#endif /* !LINKED_LIST_H_ */
