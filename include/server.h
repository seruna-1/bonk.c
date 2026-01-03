#pragma once

#include <enet/enet.h>

#include "exchangeable.h"

#define MAX_PLAYERS 8

struct ServerNetworking
{
	ENetHost *host;
	ENetAddress address;
	ENetEvent event;
};

struct Server
{
	struct ServerNetworking networking;
	struct ExchangeblePlayer player_pool[MAX_PLAYERS];
};