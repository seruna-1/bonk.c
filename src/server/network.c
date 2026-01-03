#include "server.h"

static
void
server_handle_network_event_connection
(void)
{
	printf("Player connected.\n");
/*
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!playerPool[i].active)
		{
			playerPool[i].active = true;
			playerPool[i].id = i;

			// 2. Create Box2D Body
			b2BodyDef bodyDef = b2_defaultBodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position = (b2Vec2){10.0f + i, 10.0f}; // Spread them out
			playerPool[i].bodyId = b2CreateBody(world, &bodyDef);

			b2Circle circle = { .radius = 0.5f };
			b2CreateCircleShape(playerPool[i].bodyId, &b2_defaultShapeDef, &circle);

			// 3. Link the peer to our player data
			event.peer->data = &playerPool[i];
			break;
		}
	}
*/
}

static
void
server_handle_network_event_disconnection
(void)
{
	printf("Player disconnected.\n");
}

static
void
server_handle_network_event_stillness
(void)
{
	return;
}

static
void
server_handle_network_event_reception
(void)
{
	return;
}

static
void
server_handle_network_event
(ENetEvent event)
{
	switch (event.type)
	{
		case ENET_EVENT_TYPE_CONNECT:
			server_handle_network_event_connection();
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			server_handle_network_event_disconnection();
			break;

		case ENET_EVENT_TYPE_RECEIVE:
			server_handle_network_event_reception();
			break;

		case ENET_EVENT_TYPE_NONE:
			server_handle_network_event_stillness();
			break;
	}
}

static
bool
server_network_initialize
(struct ServerNetworking *networking)
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "Failed to initialize enet.\n");
		return false;
	}

	networking->address = (ENetAddress){ .host = ENET_HOST_ANY, .port = 1234 };

	networking->host = enet_host_create(&networking->address, MAX_PLAYERS, 2, 0, 0);
	if (networking->host == NULL)
	{
		fprintf(stderr, "Failed to initialize server ENetHost.\n");
		return false;
	}
	else
	{
		printf("Server started on port %d.\n", networking->address.port);
		return true;
	}

	return false;
}
