trout: main.c trout.o util.o
	gcc -g -Wall -o trout main.c trout.o util.o

util.o: util.h util.c
	gcc -c -Wall util.c

trout.o: trout.h trout.c util.h
	gcc -c -Wall trout.c

main.o: main.c util.h trout.h
	gcc -c -Wall main.c