#makefile hex
CC=gcc
OPT=-Wall -g
EXEC= binary
all : $(EXEC)


#compile hex.c
hex.o: hex.c
	$(CC) -o hex.o -c hex.c $(OPT)


#compile main
main.o : main.c
	$(CC) -o main.o -c main.c $(OPT)


#link joueur, hex et main

$(EXEC):  hex.o main.o
	$(CC) hex.o main.o -o $(EXEC)



clean:
	rm -rf *.o *.exe *.out $(EXEC)


