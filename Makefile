CC = gcc
Flags = -Wall -g 

all: graph
 
graph : main.o graph.o
	$(CC) $(Flags) main.o graph.o -o graph

graph.o : graph.c graph.h
	$(CC) -c graph.c

main.o : main.c graph.h
	$(CC) -c main.c	

.PHONY:clean all

clean:
	rm -f *.o graph