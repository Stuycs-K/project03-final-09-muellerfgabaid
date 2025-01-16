.PHONY: clean compile
compile: client.o server.o pipe_networking.o parse_data.o game.o subserver.o testing_server.o
	@gcc -o client client.o pipe_networking.o parse_data.o game.o
	@gcc -o server server.o pipe_networking.o parse_data.o game.o subserver.o
	@gcc -o testing_server testing_server.o pipe_networking.o parse_data.o game.o
client.o: client.c pipe_networking.h parse_data.h
	@gcc -c client.c
server.o: server.c pipe_networking.h parse_data.h subserver.h
	@gcc -c server.c
pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c
parse_data.o: parse_data.c parse_data.h
	@gcc -c parse_data.c
game.o: game.c game.h
	@gcc -c game.c
subserver.o: subserver.c subserver.h
	@gcc -c subserver.c
testing_server.o: testing_server.c
	@gcc -c testing_server.c
clean:
	@rm -f *.o client server testing_server
