#include "pipe_networking.h"
#include "game.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  play_game_client(to_server, from_server);
}
