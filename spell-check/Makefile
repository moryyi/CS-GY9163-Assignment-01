default: spell_check

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell_check: dictionary.o
	gcc -Wall spell.c dictionary.o -o spell_check

clean:
	rm -rf spell_check dictionary.o
