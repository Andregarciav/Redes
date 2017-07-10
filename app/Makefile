all: teste
teste:	main.o funcoes.o
	gcc -o teste main.o funcoes.o 
main.o:  main.c
	gcc -c main.c
funcoes.o: funcoes.o
	gcc -c funcoes.c
clean:
	rm teste *.o
