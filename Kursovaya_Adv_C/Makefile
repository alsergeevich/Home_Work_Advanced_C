all: program

program: main.o functions.o
	gcc -o program main.o functions.o

main.o: main.c functions.h
	gcc -c -o main.o main.c

functions.o: functions.c
	gcc -c -o functions.o functions.c

clean:
	rm -rf *.o program