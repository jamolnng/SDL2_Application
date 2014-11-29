#pragma once

#include "GameActivity.h"
#include <SDL.h>
#include <SDL_Application.h>

int main(int argc, char* args[])
{
	GameActivity game;
	SDL_Application app(&game, true, 2, 1);
	if (app.init())
	{
		if (app.createWindow("SDL_App_Box2D_Test", 854, 500, SDL_WINDOW_RESIZABLE))
		{
			app.start();
		}
	}
	return app.finish();
}