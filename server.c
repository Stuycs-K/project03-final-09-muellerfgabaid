#include "game.h"
#include "pipe_networking.h"
#include "subserver.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <unistd.h>

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

struct client *add_client(struct client *clients, int *num_clients,
                          int *clients_max, struct client client) {
    if (num_clients >= clients_max) {
        *clients_max *= 2;
        *clients_max += 1;
        clients = realloc(clients, *clients_max * sizeof(struct client));
    }
    clients[*num_clients] = client;
    *num_clients += 1;
    return clients;
}

struct client *add_client_user(struct client *clients, int *num_clients,
                          int *clients_max, struct client client) {
    if (num_clients >= clients_max) {
        *clients_max *= 2;
        *clients_max += 1;
        clients = realloc(clients, *clients_max * sizeof(struct client));
    }
    clients[*num_clients] = client;
    *num_clients += 1;
    return clients;
}

void remove_client_user(struct client *clients, int *num_clients, int index) {
    clients[index] = clients[*num_clients - 1];
    *num_clients -= 1;
}

int main() {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, sighandler);

    printf("Hit enter to start tournament\n");

    struct client *clients = malloc(10 * sizeof(struct client));
    int num_clients = 0;
    int clients_max = 10;

    struct client *clients_user = malloc(10 * sizeof(struct client *));
    int num_clients_user = 0;
    int clients_max_user = 10;

    int from_client = server_setup();
    int max = from_client;

    while (1) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(from_client, &set);
        FD_SET(STDIN_FILENO, &set);

        for (int i = 0; i < num_clients_user; i++) {
            FD_SET(clients_user[i].from_client, &set);
        }

        select(max + 1, &set, NULL, NULL, NULL);

        if (FD_ISSET(from_client, &set)) {
            remove(WKP);
            int to_client;
            server_handshake_half(&to_client, from_client);
            struct client client;
            client.to_client = to_client;
            client.from_client = from_client;
            clients_user = add_client_user(clients_user, &num_clients_user, &clients_max_user, client);

            from_client = server_setup();
            if (from_client > max) {
                max = from_client;
            }
        } else if (FD_ISSET(STDIN_FILENO, &set)) {
            char empty;
            int bytes = read(STDIN_FILENO, &empty, 1);
            if (bytes == -1) {
                printf("%s\n", strerror(errno));
            }
            if (bytes > 0) {
                printf("Done connecting clients\n");
                break;
            }
        } else {
            struct client client;
            for (int i = 0; i < num_clients_user; i++) {
                if (FD_ISSET(clients_user[i].from_client, &set)) {
                    client = clients_user[i];
                    remove_client_user(clients_user, &num_clients_user, i);
                    break;
                }
            }
            read(client.from_client, client.user, MAX_USERNAME);
            clients = add_client(clients, &num_clients, &clients_max, client);
            printf("%s joined\n", client.user);
        }
    }

    int fd = fork_subserver(clients, num_clients);
    struct client winner;
    read(fd, &winner, sizeof(struct client));

    printf("%s won the whole tournament!!!!\n", winner.user);

    free(clients);
    remove(WKP);
}
