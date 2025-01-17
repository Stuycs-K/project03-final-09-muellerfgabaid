#ifndef GAME_H
#define GAME_H
#define MAX_USERNAME 100
struct client {
    int to_client;
    int from_client;
    char user[MAX_USERNAME];
};
void send_to_client(int client, int data);
int get_winner(int r1, int r2);
void play_game_server(struct client *client1, struct client *client2,
                      struct client *result);
int get_user_turn();
void play_game_client(int to_server, int from_server);
void get_username(char *client, int n);
void reconnect_client(int to_server, int from_server);
#endif
