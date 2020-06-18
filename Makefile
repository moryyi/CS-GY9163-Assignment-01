default: spell_check

get-deps:
	sudo apt-get install -y build-essential check

spell.o: ./spell-check/spell.c
	gcc -Wall -c ./spell-check/spell.c ./spell-check/dictionary.h

spell_check: spell.o
	gcc -Wall ./spell-check/main.c spell.o

test: ./tests/test_spell.c spell.o
	gcc -Wall -o test_spell ./tests/test_spell.c spell.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_spell

clean:
	rm -rf spell_check *.o ./spell-check/*.gch
