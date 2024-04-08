##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

OTHER	=	char_to_int.c		\
			int_to_char.c		\

FILE	=	open_file.c			\
			overwrite_in_file.c	\
			write_in_file.c		\

LIST	=	add_node.c			\
			create_node.c		\
			free_list.c			\
			my_list_len.c		\
			push_on_list.c		\
			print_list.c		\

STR		=	my_putstr.c				\
			my_put_nbr.c			\
			my_putchar.c			\
			my_str_isalpha_num.c	\
			my_str_isalpha.c		\
			my_letter_isalpha.c		\
			my_letter_isalpha_num.c	\
			my_str_isnum.c			\
			my_strcpy.c				\
			my_strcat.c				\
			my_strlen.c				\
			my_strncmp.c			\
			my_strcmp.c				\

SPLIT	=	my_splitstr.c			\
			my_str_to_word_array.c	\

TAB		=	my_tablen.c				\
			free_tab.c				\
			my_tabcpy.c				\
			tab_generator.c			\


DIR_LIST	=	$(addprefix linked_list/, $(LIST))

DIR_STR		=	$(addprefix str/, $(STR))

DIR_TAB		=	$(addprefix tab/, $(TAB))

DIR_SPLIT	=	$(addprefix spliter/, $(SPLIT))

DIR_OTHER	=	$(addprefix other/, $(OTHER))

DIR_FILE	=	$(addprefix file/, $(FILE))

OBJ_LIST	=	$(DIR_LIST:.c=.o)

OBJ_FILE	=	$(DIR_FILE:.c=.o)

OBJ_STR		=	$(DIR_STR:.c=.o)

OBJ_TAB		=	$(DIR_TAB:.c=.o)

OBJ_SPLIT	=	$(DIR_SPLIT:.c=.o)

OBJ_OTHER	=	$(DIR_OTHER:.c=.o)

OBJ			=	$(OBJ_LIST) $(OBJ_STR) $(OBJ_TAB) $(OBJ_SPLIT) $(OBJ_OTHER) \
				$(OBJ_FILE)

NAME		=	libmy.a

CPPFLAGS	=	-I./include/


DEBUG		=	-ggdb3

$(NAME):	$(OBJ)
	ar rc $@ $^
	mv $(NAME) ../

all:	$(NAME)

re: fclean $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

.PHONY: all clean fclean
