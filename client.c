#include "game.h"
#include "pipe_networking.h"
#include <stdio.h>

int main() {

    int to_server;
    int from_server;

    from_server = client_handshake(&to_server);

    printf("Connected to server\n");

    char username[MAX_USERNAME];
    get_username(username, MAX_USERNAME);

    write(to_server, username, MAX_USERNAME);

    play_game_client(to_server, from_server);
}
