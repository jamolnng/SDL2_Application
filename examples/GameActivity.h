#pragma once

#include "World.h"
#include <SDL_Activity.h>

class GameActivity : public SDL_Activity
{
	public:
		GameActivity(void);
		~GameActivity(void);

		void updateDynamic(int deltaTime);

		void updateFixed(void);

		void render(void);

		void init(void);

		void dispose(void);

		void onEvent(SDL_Event& sdl_event);

		bool initGL(void);

	private:
		World world;
};