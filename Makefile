##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##



program:
	make -C lib/my/
	make -C server/
	make -C client/


debug: $(OBJ)
	make -C lib/my/
	make debug -C server/
	make debug -C client/

all: $(NAME)

clean:
	rm vgcore*
	make clean -C lib/my/
	make clean -C server/
	make clean -C client/

fclean:
	make fclean -C lib/my/
	make fclean -C server/
	make fclean -C client/

re: fclean program

unit_tests: fclean
	make -C lib/my/
	make unit_tests -C server/
	# make unit_tests -C client/

tests_run:	unit_tests
	./server/unit_tests/unit_tests
	# ./client/unit_tests

.PHONY: all clean fclean re unit_tests tests_run
