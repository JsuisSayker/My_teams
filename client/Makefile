##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.c						\
				check_arguments.c			\
				display_help.c				\
				is_good_number.c			\
				client_logout.c				\
				spliter_by_sep.c			\
				client_connection.c			\
				user_input_event.c			\
				send_client_message.c		\
				clean_server_command.c		\
				free_client_struct.c		\
				read_server_message.c		\
				receive_server_message.c	\
				convert_string_to_time_t.c	\
				print_error_message.c		\
				handle_server_code.c

COMMANDS_SRC	=	list_command.c			\
					login_command.c			\
					logout_command.c		\
					messages_command.c		\
					send_command.c			\
					subscribe_command.c		\
					subscribed_command.c	\
					unsubscribe_command.c	\
					user_command.c			\
					users_command.c			\
					use_command.c			\
					help_command.c			\
					info_command.c			\
					create_command.c

TEST		=	test.c

DIR_SRC		=	$(addprefix src/, $(SRC))
DIR_COMMANDS =  $(addprefix src/commands/, $(COMMANDS_SRC))
DIR_TESTS	=	$(addprefix tests/, $(TEST))


OBJ_SRC		=	$(DIR_SRC:.c=.o)
COMMANDS_OBJ	 =       $(DIR_COMMANDS:.c=.o)

OBJ			=	$(OBJ_SRC) $(COMMANDS_OBJ)

NAME		=	myteams_cli

LDLIB		=	-L../lib/ -L../libs/myteams/

LMY			=	-lmy -lmyteams

CPPFLAGS	=	-I../include/ -I../lib/my/include/ -I../libs/myteams/

WFLAGS		=	-W -Wall -Wextra -Werror

LCRITER		= --coverage -lcriterion

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CPPFLAGS) $(WFLAGS) $(LDLIB) $(LMY)
	mv $(NAME) ../

debug:
	gcc -o $(NAME) $(DIR_SRC) $(DIR_COMMANDS) $(CPPFLAGS) $(LDLIB) $(LMY) \
	-ggdb3
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
