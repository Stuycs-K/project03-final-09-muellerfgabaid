#include "pipe_networking.h"
#include "subserver.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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
    if (syn_ack < 0)
        syn_ack *= -1;

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

int **add_client(int **clients, int *num_clients, int *clients_max,
                 int to_client, int from_client) {
    if (num_clients >= clients_max) {
        *clients_max = *clients_max * 2 + 1;
        clients = realloc(clients, *clients_max * 2 * sizeof(int));
    }
    *num_clients += 1;
    clients[*num_clients][0] = from_client;
    clients[*num_clients][1] = to_client;
    return clients;
}

int main() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sighandler);

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);

    printf("Hit enter to start game\n");

    int **clients = malloc(10 * sizeof(int) * 2);
    int num_clients = 0;
    int clients_max = 10;

    while (1) {
        int from_client = server_setup();
        printf("New player joined\n");

        int to_client;
        server_handshake_half(&to_client, from_client);

        clients = add_client(clients, &num_clients, &clients_max, to_client,
                             from_client);

        char empty;
        if (read(STDIN_FILENO, &empty, 1) > 0) {
            printf("Done connecting clients\n");
            break;
        }
    }

    int fd = fork_subserver(clients, num_clients);
    int winner[2];
    read(fd, winner, sizeof(int) * 2);
    // the winner is ...
}
