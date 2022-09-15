main: main.o
	cc main.o -o main
	rm -f main.o
main.o:
	cc -c main.c -o main.o
main.c:

