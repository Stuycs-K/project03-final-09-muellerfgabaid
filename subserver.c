#include "subserver.h"
#include "game.h"
#include "pipe_networking.h"
#include <stdlib.h>
#include <unistd.h>

// TODO replace fds[0/1] with constants before merging
int fork_subserver(struct client *clients, int num_clients) {
    int fds[2];
    pipe(fds);
    int pid = fork();
    if (pid == 0) {
    	if (num_clients == 0) {
    		perror("NO CLIENTS CONNECT... EXITING\n");
    		exit(1);
    	}
        if (num_clients == 1) {
            write(fds[1], clients, sizeof(struct client));
        } else {
            int subserver1 = fork_subserver(clients, num_clients / 2);
            int subserver2 =
                fork_subserver(clients + (num_clients / 2),
                               num_clients - num_clients / 2);
            struct client player1;
            struct client player2;
            read(subserver1, &player1, sizeof(struct client));
            read(subserver2, &player2, sizeof(struct client));
            struct client winner;
            // play game with player1 and player2
            play_game_server(&player1, &player2, &winner);
            write(fds[1], &winner, sizeof(struct client));
        }
        exit(EXIT_SUCCESS);
    }
    return fds[0];
}
