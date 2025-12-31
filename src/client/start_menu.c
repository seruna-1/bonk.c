#include "client/game.h"

static inline
enum GameSegment
game_start_menu_handle
(void)
{
	BeginDrawing();
	{
		ClearBackground(WHITE);
		DrawText("Bonk.c", 20, 20, 20, BLACK);
	}
	EndDrawing();

	if ( WindowShouldClose() )
	{
		return NONE;
	}
	else if ( IsKeyPressed(KEY_M) )
	{
		return MULTIPLAYER;
	}
	else if ( IsKeyPressed(KEY_S) )
	{
		return SINGLEPLAYER;
	}
	else
	{
		return START_MENU;
	}
}
