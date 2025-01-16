#include "pipe_networking.h"
#include "parse_data.h"
#include "game.h"

void send_to_client(int * client, int data) {
	int send = data;
	write(*client, &send, sizeof(send));
}

int get_winner(int r1, int r2) { // Returns 0 for tie, 1 for client 1 win, 2 for client 2 win
	int offset = (r1 + 1) % 3;
	if (offset == r2) {
		return 2;
	} else if (offset == r2 + 1) {
		return 0;
	} else {
		return 1;
	}
}

void play_game_server(int * to_client1, int * to_client2, int * from_client1, int * from_client2, int * result) {
	send_to_client(to_client1, USER_TURN); // Tells client1 that it's its turn

	send_to_client(to_client2, OPP_TURN); // Tells client2 that it is the opponent's turn

	int response_1;
	int bytes = read(*from_client1, &response_1, sizeof(response_1)); // Reads client's choice; Already validated by client
	printf("%d b: %d,\n%s\n", *from_client1, bytes, strerror(errno));
	if (bytes > 0) {
		send_to_client(to_client2, USER_TURN);
		send_to_client(to_client1, OPP_TURN);
	}

	int response_2;
	bytes = read(*from_client2, &response_2, sizeof(response_2));
	
	if (bytes > 0) {
		int outcome = get_winner(response_1, response_2);
		if (outcome == 0) {
			send_to_client(to_client1, TIE);
			send_to_client(to_client2, TIE);
			play_game_server(to_client1, to_client2, from_client1, from_client1, result);
		} else if (outcome == 1) {
			send_to_client(to_client1, WIN);
			send_to_client(to_client2, LOSE);
			result[0] = to_client1[0];
			result[1] = to_client1[1];
		} else {
			send_to_client(to_client1, LOSE);
			send_to_client(to_client2, WIN);
			result[0] = to_client2[0];
			result[1] = to_client2[1];
		}
	}
}

int get_user_turn() {
	char buffer[50];
	printf("Your Turn!\nEnter your move: (rock/paper/scissors)\n");
	fgets(buffer, 49, stdin);
	if (!strcmp(buffer, "rock\n")) {
		return ROCK;
	} else if (!strcmp(buffer, "paper\n")) {
		return PAPER;
	} else if (!strcmp(buffer, "scissors\n")) {
		return SCISSORS;
	} else {
		printf("Invalid Input.\n");
		return get_user_turn();
	}
}

void play_game_client(int to_server, int from_server) {
	int data = 0;
	read(from_server, &data, sizeof(data));

	if (data == USER_TURN) {
		int turn = get_user_turn();
		write(to_server, &turn, sizeof(turn));
		play_game_client(to_server, from_server);
	} else if (data == OPP_TURN){
		printf("Waiting for opponent...\n");
		play_game_client(to_server, from_server);
	} else if (data == WIN) {
			printf("You Win!\n");
	} else if (data == LOSE) {
			printf("You Lose.\n");
	} else if (data == TIE) {
			printf("You Tied...\n");
	}
}
