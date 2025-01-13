#include "pipe_networking.h"
#include "parse_data.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  int in;
  char input[100];
  int out = 0;
  while (1) {
    read(from_server, &in, sizeof(in));
    if (in == WIN) {
      printf("You Win!\n");
      exit(0);
    } else if (in == LOSE) {
      printf("You Lost :(\n");
      exit(0);
    }
    if (in == USER_TURN) {
      getInput(from_server, to_server);
    } else if (in == OPP_TURN) {
      printf("Waiting for opponent...\n");
    }
    sleep(1);
  }
}
