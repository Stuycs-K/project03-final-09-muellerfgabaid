#include "pipe_networking.h"
#include "parse_data.h"
#include "game.c"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  play_game_client(to_server, from_server);
}
