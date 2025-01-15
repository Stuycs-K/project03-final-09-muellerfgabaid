#include "subserver.h"
#include "game.h"
#include "pipe_networking.h"
#include <stdlib.h>
#include <unistd.h>

// TODO replace fds[0/1] with constants before merging
int fork_subserver(int *clients, int num_clients) {
    int fds[2];
    pipe(fds);
    int pid = fork();
    if (pid == 0) {
    	if (num_clients == 0) {
    		perror("NO CLIENTS CONNECT... EXITING\n");
    		exit(1);
    	}
        if (num_clients == 1) {
            write(fds[1], clients, 2 * sizeof(int));
        } else {
            int subserver1 = fork_subserver(clients, num_clients / 2);
            int subserver2 =
                fork_subserver(clients + (num_clients / 2) * sizeof(int),
                               num_clients - num_clients / 2);
            int player1[2];
            int player2[2];
            read(subserver1, player1, 2 * sizeof(int));
            read(subserver2, player2, 2 * sizeof(int));
            int winner[2];
            // play game with player1 and player2
            play_game_server(player1, player2, winner);
            write(fds[1], winner, 2 * sizeof(int));
        }
        exit(EXIT_SUCCESS);
    }
    return fds[0];
}
