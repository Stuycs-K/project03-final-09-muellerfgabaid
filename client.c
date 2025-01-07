#include "pipe_networking.h"
#include "parseData.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  char in[100];
  char msg_type[100];
  char data[100];
  int out = 1;
  while (1) {
    read(from_server, &in, sizeof(in));
    parseServerResponse(in, msg_type, data);
    if (!strcmp(msg_type, "TURN")) {
      if (!strcmp(data, "0")) {
        printf("Your Turn\n");
        //write(to_server, &out, sizeof(out));
      } else {
        printf("Enemy Turn\n");
      }
    }
    sleep(1);
  }
}