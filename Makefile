.PHONY: clean all
all: server client
client: client.o pipe_networking.o
	@gcc -o client client.o pipe_networking.o
server: server.o pipe_networking.o
	@gcc -o server server.o pipe_networking.o
client.o: client.c pipe_networking.h
	@gcc -c client.c
server.o: server.c pipe_networking.h
	@gcc -c server.c
clean:
	@rm -f *.o client server
