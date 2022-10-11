CC = gcc
FLAGS = -g -Wall -Werror -std=c99

OBJS = main.o pcv.o lista.o cidade.o
BIN = pcv

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(BIN)

main.o: main.c 
	$(CC) $(FLAGS) -c main.c

pcv.o: src/pcv.c Includes/pcv.h
	$(CC) $(FLAGS) -c source_files/pcv.c

lista.o: src/lista.c headers/lista.h
	$(CC) $(FLAGS) -c source_files/lista.c

cidade.o: src/cidade.c headers/cidade.h
	$(CC) $(FLAGS) -c source_files/cidade.c
	 
clean:
	rm *.o $(BIN)

run:
	./$(BIN)

valgrind:
	valgrind ./$(BIN)