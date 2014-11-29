#pragma once

#include <SDL.h>
#include "SDL_keyboard.h"

class Keyboard
{
	public:
		Keyboard(void);
		~Keyboard(void);

		void clear(void);
		void onEvent(SDL_Event &sdl_event);
};