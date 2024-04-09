##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.c

TEST		=	test.c

DIR_SRC		=	$(addprefix src/, $(SRC))
DIR_TESTS	=	$(addprefix tests/, $(TEST))

OBJ_SRC		=	$(DIR_SRC:.c=.o)
OBJ			=	$(OBJ_SRC)

NAME		=	myteams_server

LDLIB		=	-L../lib/

LMY			=	-lmy

CPPFLAGS	=	-I./includes/ -I../lib/my/include/

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
	rm -f $(OBJ)
	make clean -C ../lib/my/

fclean: clean
	rm -f ../$(NAME)
	rm -rf unit_tests/
	make fclean -C ../lib/my/

re: fclean $(NAME)

unit_tests: fclean
	mkdir unit_tests
	gcc -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS) $(LDLIB) $(LMY) \
	$(CPPFLAGS) $(WFLAGS) $(LCRITER)

tests_run:	unit_tests
	./unit_tests

.PHONY: all clean fclean re unit_tests tests_run