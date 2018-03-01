cf: main.o c2f.o f2c.o
	gcc main.o c2f.o f2c.o -o cf

main.o: main.c cf.h
	gcc -Wall -Werror -ggdb main.c -c

c2f.o: c2f.c cf.h
	gcc -Wall -Werror -ggdb c2f.c -c

f2c.o: f2c.c cf.h
	echo Building f2c.o
	gcc -Wall -Werror -ggdb f2c.c -c

clean:
	rm -f *.o cf *~ core
