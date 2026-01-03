#include "server.h"
#include <stdio.h>

// From network.c

static inline
void
server_handle_network_event
(ENetEvent event);

static
bool
server_network_initialize
(struct ServerNetworking *networking);

#include "network.c"

#include "world.c"

int
main
(void)
{
	struct Server server = {0};

	if (!server_network_initialize(&server.networking))
	{ return EXIT_FAILURE; }

	bool keep_server_running = true;
	while (keep_server_running)
	{
		if (enet_host_service(server.networking.host, &server.networking.event, 1000) > 0)
		{ server_handle_network_event(server.networking.event); }
	}

	enet_host_destroy(server.networking.host);
	printf("Enet host destroyed.\n");

	return EXIT_SUCCESS;
}