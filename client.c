#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  int in;
  int out = 0;
  while (1) {
    read(from_server, &in, sizeof(in));
    if (in == 1) {
      printf("Your Turn\n");
    } else if (in == 0){
      printf("Enemy Turn\n");
    }
    write(to_server, &out, sizeof(out));
    sleep(1);
  }
}