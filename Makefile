FLAGS = -Wall -Wextra -Werror -std=c11
FILES = func_4_6.c test_4_6.c

all: test 
	
clang:
	clang-format --style=Google -n *.c *.h
	clang-format --style=Google -i *.c *.h

clean:
	rm -rf test

test:
	rm -rf test
	gcc $(FLAGS) -o test $(FILES)
	./test



