#include "pipe_networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server

/*=========================
  server_setup

  creates the WKP and opens it, waiting for a connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  mkfifo(WKP, 0666);
  from_client = open(WKP, O_RDONLY);
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();

  char clientPipe[100];
  if (read(from_client, clientPipe, sizeof(clientPipe)) == -1) {
    printf("SYN READ FAIL\n");
    exit(1);
  } else {
    printf("[SYN READ]: %s\n", clientPipe);
  }

  *to_client = open(clientPipe, O_WRONLY);

  int syn_ack;
  int rfile = open("/dev/urandom", O_RDONLY, 0);
  read(rfile, &syn_ack, 2);
  if (syn_ack < 0) syn_ack *= -1;
  
  if (write(*to_client, &syn_ack, sizeof(syn_ack)) == -1) {
    printf("SYN_ACK SEND FAIL\n");
    exit(1);
  } else {
    printf("[SYN_ACK SENT]: %d\n", syn_ack);
  }

  int ack;
  if (read(from_client, &ack, sizeof(ack)) == -1) {
    printf("ACK READ FAIL\n");
    exit(1);
  } else {
    printf("[ACK READ]: %d\n", ack);
  }

  if (ack != syn_ack + 1) {
    printf("INVALID ACK\n");
    exit(1);
  }

  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;

  char pidPipe[100];
  int pid = getpid();
  sprintf(pidPipe, "%d", pid);
  mkfifo(pidPipe, 0666);

  *to_server = open(WKP, O_WRONLY);
  if (write(*to_server, pidPipe, sizeof(pidPipe)) == -1) {
    printf("SYN SEND FAIL\n");
    exit(1);
  } else {
    printf("[SYN SENT]: %d\n", pid);
  }

  from_server = open(pidPipe, O_RDONLY);
  int syn_ack;
  if (read(from_server, &syn_ack, sizeof(syn_ack)) == -1) {
    printf("SYN_ACK READ FAIL\n");
    remove(pidPipe);
    exit(1);
  } else {
    printf("[SYN_ACK READ]: %d\n", syn_ack);
    remove(pidPipe);  
  }

  int ack = syn_ack + 1;
  if (write(*to_server, &ack, sizeof(ack)) == -1) {
    printf("ACK SEND FAIL\n");
    exit(1);
  } else {
    printf("[ACK SENT]: %d\n", ack);
  }

  remove(pidPipe);
  return from_server;
}
