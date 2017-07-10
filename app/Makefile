all: teste
teste: funcoes.o main.o
	gcc -o teste funcoes.o main.o 
main.o:  main.c
	gcc -c main.c
funcoes.o: funcoes.o
	gcc -c funcoes.c
clean:
	rm teste *.o
