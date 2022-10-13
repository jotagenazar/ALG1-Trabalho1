CC = gcc
FLAGS = -g -Wall -Werror -std=c99

OBJS = main.o pcv.o lista.o cidade.o
BIN = pcv

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(BIN)

main.o: main.c 
	$(CC) $(FLAGS) -c main.c

pcv.o: src/pcv.c includes/pcv.h
	$(CC) $(FLAGS) -c src/pcv.c

lista.o: src/lista.c includes/lista.h
	$(CC) $(FLAGS) -c src/lista.c

cidade.o: src/cidade.c includes/cidade.h
	$(CC) $(FLAGS) -c src/cidade.c
	 
clean:
	rm *.o $(BIN)

run:
	./$(BIN)

valgrind:
	valgrind ./$(BIN)