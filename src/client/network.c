#include "client/game.h"

static inline
bool
game_network_connect
(struct GameNetworking *networking)
{
	enet_initialize();

	// Create client ENetHost

	networking->client = enet_host_create(NULL, 1, 2, 0, 0);
	if (networking->client == NULL)
	{
		fprintf(stderr, "Failed to initialize client ENetHost.\n");
		return false;
	}
	else
	{ printf("Initialized client ENetHost.\n"); }

	// Connect to server peer

	enet_address_set_host(&networking->address, "127.0.0.1");
	networking->address.port = 1234;

	networking->server = enet_host_connect(networking->client, &networking->address, 2, 0);
	if (networking->server == NULL)
	{
		fprintf(stderr, "Server peer isn't avaiavble for initiating an ENet connection.\n");
		return false;
	}

	// Wait for a connect event at server

	if
	(
		enet_host_service(networking->client, &networking->event, 5000) > 0
		&& networking->event.type == ENET_EVENT_TYPE_CONNECT
	)
	{
		puts("Connection to server succeeded.\n");
		return true;
	}

	enet_peer_reset(networking->server);
	fprintf(stderr, "Connection to server failed. No connect event got.\n");
	return false;
}

static inline
bool
game_network_update
(struct Game *game)
{
	switch (game->networking.state)
	{
		case CONNECTING:
			if (!game_network_connect(&game->networking))
			{ return false; }
			else { game->networking.state = CONNECTED; }
			break;
		case CONNECTED:
			enet_host_service(game->networking.client, &game->networking.event, 30);
			break;
		case DISCONNECTING:
		case DISCONNECTED:
			return false;
			break;
	}

	switch (game->networking.event.type)
	{
		case ENET_EVENT_TYPE_CONNECT:
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			return false;
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			break;
		case ENET_EVENT_TYPE_NONE:
			break;
	}
	return true;
}
