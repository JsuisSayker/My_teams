##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	display_help.c \
				server.c \
				free.c \
				socket.c

MAIN_SRC	=	main.c

TEST		=	test.c

DIR_SRC		=	$(addprefix src/, $(SRC))
DIR_MAIN	=	$(addprefix src/, $(MAIN_SRC))
DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_SRC		=	$(DIR_SRC:.c=.o)
OBJ_MAIN	=	$(DIR_MAIN:.c=.o)
OBJ			=	$(OBJ_SRC) \
				$(OBJ_MAIN)

NAME		=	myteams_server

LDLIB		=	-L../lib/ -L../libs/myteams/

LMY			=	-lmy -lmyteams

CPPFLAGS	=	-I../include/ -I../lib/my/include/ -I../libs/myteams/

WFLAGS		=	-W -Wall -Wextra -Werror

LCRITER		= --coverage -lcriterion

$(NAME): $(OBJ)
	gcc -o $@ $^ $(WFLAGS) $(LDLIB) $(LMY)
	mv $(NAME) ../

debug: $(OBJ)
	gcc -o $(NAME) $^ $(CPPFLAGS) $(WFLAGS) $(LDLIB) $(LMY) -ggdb3
	mv $(NAME) ../

all: $(NAME)

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f ../$(NAME)
	@ rm -rf unit_tests/

re: fclean $(NAME)

unit_tests: fclean
	mkdir unit_tests
	gcc -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS) $(LDLIB) $(LMY) \
	$(CPPFLAGS) $(WFLAGS) $(LCRITER)

tests_run:	unit_tests
	./unit_tests

.PHONY: all clean fclean re unit_tests tests_run
