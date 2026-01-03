#include "game.h"
#include "network.c"

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

		BeginDrawing();
		ClearBackground(WHITE);
		DrawText(
			"We are in multiplayer :3\n",
			20,
			20,
			20,
			BLACK
		);
		EndDrawing();
	}

	enet_peer_reset(game->networking.server);
	enet_host_destroy(game->networking.client);
	printf("ENetHost client destroyed.\n");

	return START_MENU;
}