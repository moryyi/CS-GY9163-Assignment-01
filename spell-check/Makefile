default: spell_check

spell.o: spell.c
	gcc -Wall -c spell.c dictionary.h

spell_check: spell.o
	gcc -Wall test_main.c spell.o -o spell_check

clean:
	rm -rf spell_check *.o *.gch
