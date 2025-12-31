#include "client/game.h"
#include "./network.c"

static inline
enum GameSegment
game_multiplayer_handle
(struct Game *game)
{
	printf("Starting multiplayer.\n");

	while (!WindowShouldClose() && game->networking.state != DISCONNECTING)
	{
		if (!game_network_update(game))
		{ game->networking.state = DISCONNECTING; }
	}

	enet_peer_reset(game->networking.server);
	enet_host_destroy(game->networking.client);
	printf("ENetHost client destroyed.\n");

	return START_MENU;
}