#ifndef GAME_H
#define GAME_H
void send_to_client(int * client, int data);
int get_winner(int r1, int r2);
void play_game_server(struct client client1, struct client client2, int * result);
int get_user_turn();
void play_game_client(int to_server, int from_server);
struct client {
	int to_client;
	int from_client;
	char user[100];
}
#endif
