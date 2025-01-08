.PHONY: clean compile
compile: client.o server.o pipe_networking.o parse_data.o
	@gcc -o client client.o pipe_networking.o parse_data.o
	@gcc -o server server.o pipe_networking.o parse_data.o
client.o: client.c pipe_networking.h
	@gcc -c client.c
server.o: server.c pipe_networking.h
	@gcc -c server.c
pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c
parse_data.o: parse_data.c parse_data.h
	@gcc -c parse_data.c
clean:
	@rm -f *.o client server
