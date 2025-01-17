#ifndef GAME_H
#define GAME_H
struct client {
	int to_client;
	int from_client;
	char user[100];
};
void send_to_client(int client, int data);
int get_winner(int r1, int r2);
void play_game_server(struct client * client1, struct client * client2, struct client * result);
int get_user_turn();
void play_game_client(int to_server, int from_server);
void get_username(struct client * client);
#endif
