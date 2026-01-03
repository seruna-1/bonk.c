#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "game.h"
#include "start_menu.c"
#include "multiplayer.c"
#include "singleplayer.c"

int
main
(void)
{
	InitWindow(500, 500, "Bonk.c");
	SetTargetFPS(60);

	struct Game game = {0};
	enum GameSegment segment = START_MENU;

	while (segment != NONE)
	{
		switch (segment)
		{
			case START_MENU:
				segment = game_start_menu_handle();
				break;
			case MULTIPLAYER:
				segment = game_multiplayer_handle(&game);
				break;
			case SINGLEPLAYER:
				segment = game_singleplayer_handle(&game);
				break;
			case NONE:
				break;
		}
	}

	return EXIT_SUCCESS;
}