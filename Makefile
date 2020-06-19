default: prog

get-deps:
	sudo apt-get install -y build-essential check afl

dictionary.o: ./spell-check/dictionary.c
	gcc -Wall -c ./spell-check/dictionary.c -o dictionary.o

spell.o: ./spell-check/spell.c
	gcc -Wall -c ./spell-check/spell.c -o spell.o

test.o: ./tests/test_spell.c
	gcc -Wall -c ./tests/test_spell.c -o test.o

main.o: ./spell-check/main.c
	gcc -Wall -c ./spell-check/main.c -o main.o

test: dictionary.o spell.o test.o
	gcc -Wall -o test_spell dictionary.o spell.o test.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_spell

prog: dictionary.o spell.o main.o
	gcc -Wall -o spell_check dictionary.o spell.o main.o


afl_dictionary.o: ./spell-check/dictionary.c
	afl-gcc -Wall -c ./spell-check/dictionary.c -o afl_dictionary.o

afl_spell.o: ./spell-check/spell.c
	afl-gcc -Wall -c ./spell-check/spell.c -o afl_spell.o

afl_main.o: ./afl-tests/afl_main.c
	afl-gcc -Wall -c ./afl-tests/afl_main.c -o afl_main.o

afl: afl_dictionary.o afl_spell.o afl_main.o
	afl-gcc -Wall -o afl_test afl_dictionary.o afl_spell.o afl_main.o

clean:
	rm -rf *.o ./spell-check/*.gch

cleanall:
	rm -rf spell_check