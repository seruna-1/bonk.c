// Client

#pragma once

#include <enet/enet.h>

// Delegate is a section
enum GameSegment
{
	START_MENU,
	MULTIPLAYER,
	SINGLEPLAYER,
	NONE, // The game should end
};

struct GameNetworking
{
	enum
	{
		CONNECTING,
		CONNECTED,
		DISCONNECTING,
		DISCONNECTED,
	}
	state;

	ENetHost *client;
	ENetAddress address;
	ENetPeer *server;
	ENetEvent event;
};

struct Game
{
	struct GameNetworking networking;
	bool should_exit;
};