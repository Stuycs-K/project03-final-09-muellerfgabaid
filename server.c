#include "pipe_networking.h"
#include <signal.h>
#include <sys/wait.h>

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
        printf("SYN READ FAIL\n");
        exit(1);
    }
    *to_client = open(clientPipe, O_WRONLY);

    int syn_ack, ack;
    int rfile = open("/dev/urandom", O_RDONLY, 0);
    read(rfile, &syn_ack, sizeof(syn_ack));
    if (syn_ack < 0) syn_ack *= -1;

    if (write(*to_client, &syn_ack, sizeof(syn_ack)) == -1) {
        printf("SYN_ACK SEND FAIL\n");
        exit(1);
    }

    if (read(from_client, &ack, sizeof(ack)) == -1) {
        printf("ACK READ FAIL\n");
        exit(1);
    }

    if (ack != syn_ack + 1) {
        printf("INVALID ACK\n");
        exit(1);
    }
}

int main() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sighandler);

    printf("Waiting for client...\n");

    while (1) {
        int from_client = server_setup();
        printf("New Connection Made\n");

        pid_t p = fork();
        if (p < 0) {
            perror("Fork Fail\n");
            exit(1);
        } else if (p == 0) { //Subserver
            int to_client;
            server_handshake_half(&to_client, from_client);
            while (1) {
                int out;
                out = 1;
                write(to_client, &out, sizeof(out));
                int in;
                if (read(from_client, &in, sizeof(in)) <= 0) {
                    printf("Client lost\n");
                    close(to_client);
                    close(from_client);
                    exit(0);
                }
                printf("%d\n", in);
                sleep(1);
            }  
        } else {
            close(from_client);
        }
    }
}