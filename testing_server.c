#include "pipe_networking.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "parse_data.h"
#include "game.h"

static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        printf("Server Closed\n");
        exit(0);
    }
}

void server_handshake_half(int *to_client, int from_client) {
    char clientPipe[100];
    if (read(from_client, clientPipe, sizeof(clientPipe)) == -1) {
        perror("SYN READ FAIL");
        exit(1);
    }

    *to_client = open(clientPipe, O_WRONLY);
    if (*to_client == -1) {
        perror("CLIENT PIPE OPEN FAIL");
        exit(1);
    }

    int syn_ack, ack;
    int rfile = open("/dev/urandom", O_RDONLY);
    if (rfile == -1) {
        perror("URANDOM OPEN FAIL");
        exit(1);
    }

    if (read(rfile, &syn_ack, sizeof(syn_ack)) == -1) {
        perror("URANDOM READ FAIL");
        close(rfile);
        exit(1);
    }
    close(rfile);

    if (syn_ack < 0) syn_ack = -syn_ack;

    if (write(*to_client, &syn_ack, sizeof(syn_ack)) == -1) {
        perror("SYN_ACK SEND FAIL");
        exit(1);
    }

    if (read(from_client, &ack, sizeof(ack)) == -1) {
        perror("ACK READ FAIL");
        exit(1);
    }

    if (ack != syn_ack + 1) {
        fprintf(stderr, "INVALID ACK\n");
        exit(1);
    }
}


int main() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sighandler);

    printf("Waiting for clients...\n");
    int to_clients[2];
    int from_clients[2];
    int num = 0; 

    while (1) {
        int from_client = server_setup();
        printf("New Connection Made\n");

        int to_client;
        server_handshake_half(&to_client, from_client);
        to_clients[num] = to_client;
        from_clients[num] = from_client;
        num++;
        //close(from_client);

        if (num == 2) {
            printf("Starting game...\n");
            int result;
            play_game_server(&to_clients[0], &to_clients[1], &from_clients[0], &from_clients[1], &result);
            printf("Res: %d\n", result);
            //close(clients[0]);
            //close(clients[1]);
            num = 0; 
        }
    }

    return 0;
}
