all: item.o Pilha.o main.o pcv.o
	gcc item.o Pilha.o main.o pcv.o -o pcv -std=c99 -Wall

pcv.o:
	gcc -c pcv.c -o pcv.o

item.o:
	gcc -c item.c -o item.o

Pilha.o:
	gcc -c Pilha.c -o Pilha.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o pcv

run:
	./pcv