default: spell_check

spell.o: ./spell-check/spell.c
	gcc -Wall -c ./spell-check/spell.c ./spell-check/dictionary.h

spell_check: spell.o
	gcc -Wall ./spell-check/main.c spell.o -o $@

clean:
	rm -rf spell_check *.o ./spell-check/*.gch
