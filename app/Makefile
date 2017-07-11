Tp3: client.o server_fork.o main.o funcoes.o
	gcc -o cliente client.c -Wall -Wextra
	gcc -o servidor server_fork.o cria_usuario.o funcoes.o
server_fork.o:  server_fork.c
	gcc -c server_fork.c
main: main.o
	gcc -c main.c
funcoes: funcoes.o
	gcc -c funcoes.c
client.o: client.c
	gcc -c client.c
clean:
	rm cliente *.o
	rm servidor *.o
