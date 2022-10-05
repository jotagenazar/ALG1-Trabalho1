all: item.o Pilha.o main.o pcv.o
	gcc item.o Pilha.o main.o pcv.o -o pcv -std=c99 -Wall

pcv.o: pcv.c pcv.h
	gcc -c pcv.c -o pcv.o

item.o: item.c item.h
	gcc -c item.c -o item.o

Pilha.o: Pilha.c Pilha.h
	gcc -c Pilha.c -o Pilha.o
	 
main.o: main.c 
	gcc -c main.c -o main.o
	 
clean:
	rm *.o pcv

run:
	./pcv