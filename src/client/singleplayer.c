#include "raylib.h"

#include "client/game.h"

static inline
enum GameSegment
game_singleplayer_handle
(struct Game *game)
{
	(void)game;
	while (!WindowShouldClose() && !IsKeyPressed(KEY_ENTER))
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawText(
			"There is no handle to singleplayer yet, press ENTER to come back to start menu.\n",
			20,
			20,
			20,
			BLACK
		);

		EndDrawing();
	}
	return START_MENU;
}