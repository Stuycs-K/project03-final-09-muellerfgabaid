#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  char out[100];
  sprintf(out, "Message from client %d", getpid());
  while (1) {
    write(to_server, &out, sizeof(out));
    printf("SENT: %s\n", out);
    sleep(1);
  }
}