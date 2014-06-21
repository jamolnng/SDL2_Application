#pragma once

#include <SDL.h>

class SDL_Activity;

class GLWindow
{
	public:
		GLWindow(char* title = "SDL Layout Window", int width = 854, int height = 500, char* iconFile = "");
		~GLWindow(void);

		bool init(SDL_Activity* activity);

		void handleEvent(SDL_Event& e);
		void dispose(void);

		SDL_Window* getWindow(void);
		SDL_Renderer* getRenderer(void);

		int getWidth(void), getHeight(void);
		const char* getTitle(void);
		bool hasMouseFocus(void), hasKeyboardFocus(void), isFullscreen(void), isMinimized(void);

		bool setFullscreen(bool fullscreen);

	private:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;

		int width, height;
		char* title;
		bool mouseFocus, keyboardFocus, fullScreen, minimized;

		SDL_GLContext gl_context;
};