CC=gcc
FLAGS=-Wall -Wextra -Werror -Wvla -pedantic -fsanitize=address
OUTPUT=myfind

all: myfind
	
myfind:
	$(CC) $(FLAGS) src/**/*.c src/main.c src/my_find.c -o $(OUTPUT)

tests_loc:
	myfind
	cp myfind tests_loc/basic_find
	cp myfind tests_loc/print_action
	cp myfind tests_loc/name_test
	cp myfind tests_loc/type_test
	cp myfind tests_loc/newer_test

clean:
	-rm tests_loc/basic_find/myfind
	-rm tests_loc/print_action/myfind
	-rm tests_loc/name_test/myfind
	-rm tests_loc/type_test/myfind
	-rm tests_loc/newer_test/myfind
	-rm myfind 
