Tp3: client.o server_fork.o cria_usuario.o funcoes.o
	gcc -o cliente client.c -Wall -Wextra
	gcc -o servidor server_fork.o cria_usuario.o funcoes.o
server_fork.o:  server_fork.c
	gcc -c server_fork.c
cria_usuarios.o: cria_usuario.c
	gcc -c cria_usuario.c
funcoes.o: funcoes.o
	gcc -c funcoes.c
client.o: client.c
	gcc -c client.c
clean:
	rm cliente *.o 
	rm servidor *.o 
	
