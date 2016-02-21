
#This next line defines arguments that are passed to all compilation steps

CCFLAGS = -g -Wall

simulate: list.o process.c
	gcc $(CCFLAGS) -o simulate list.o process.c

list.o: list.c list.h
	gcc $(CCFLAGS) -c list.c

clean:
	-rm list.o simulate

