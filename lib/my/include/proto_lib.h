/*
** EPITECH PROJECT, 2023
** other
** File description:
** proto_lib
*/

#include "linked_list.h"

#ifndef PROTO_LIB_H_
    #define PROTO_LIB_H_

    /* file */
int overwrite_to_file(char *str, char *filename);
int write_to_file(char *str, char *filename);
char *open_file(char const *file);

    /* list */
int push_on_list(list_t **list_src, list_t **list_dest);
list_t *add_node_in_list(list_t *list, char *str);
int print_room_list(list_t *list, char *str);
void free_list(list_t *list);
list_t *create_node(char *str);
int my_list_len(list_t *list);
int print_list(list_t *list);
int print_node(list_t *node);
void free_node(list_t *node);

    /* spliter */
char **my_splitstr(char const *str, int separator);
char **my_str_to_word_array(char const *str);

    /* str */
int my_strncmp(char const *s1, char const *s2, int n);
int my_str_isalpha_num(char const *str, int i);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
int my_all_str_isalpha_num(char const *str);
int my_letter_isalpha_num(char letter);
int my_str_isalpha(char const *str);
int my_letter_isalpha(char letter);
int my_str_isnum(char const *str);
int my_strcpy(char const *src, char **dest);
int my_strlen(char const *str);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_putchar(char c);

    /* tab */
int tab_generator(char ***tab, int y, int x);
int my_tabcpy(char **src, char ***dest);
int my_tablen(char **tab);
void free_tab(char **tab);

    /* other */
int char_to_int(char const *str);

#endif /* !PROTO_LIB_H_ */
