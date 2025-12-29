#include <enet/enet.h>
#include <stdio.h>

const int max_players = 32;

static inline
void
server_handle_network_event_connection
(void)
{
	printf("Player connected.\n");
}

static inline
void
server_handle_network_event_disconnection
(void)
{
	printf("Player disconnected.\n");
}

static inline
void
server_handle_network_event_stillness
(void)
{
	return;
}

static inline
void
server_handle_network_event_reception
(void)
{
	return;
}

static inline
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

int
main
(void)
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "Failed to initialize enet.\n");
		return EXIT_FAILURE;
	}

	ENetAddress address = { .host = ENET_HOST_ANY, .port = 1234 };

	ENetHost *server = enet_host_create(&address, max_players, 2, 0, 0);
	if (server == NULL)
	{
		fprintf(stderr, "Failed to initialize server.\n");
		return EXIT_FAILURE;
	}
	else
	{ printf("Server started on port %d.\n", address.port); }

	bool keep_server_running = true;
	while (keep_server_running)
	{
		ENetEvent event = { 0 };

		if (enet_host_service(server, &event, 1000) > 0)
		{ server_handle_network_event(event); }
	}

	enet_host_destroy(server);
	printf("Enet host destroyed.\n");

	return EXIT_SUCCESS;
}