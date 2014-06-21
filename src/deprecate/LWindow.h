#pragma once

#include <SDL.h>

class LWindow
{
	public:
		//Intializes internals
		LWindow(char* title, int width, int height);
		~LWindow(void);

		//Creates window
		bool init(void);

		//Creates renderer from internal window
		SDL_Renderer* createRenderer(void);

		//Gets window renderer
		SDL_Renderer* getRenderer(void);

		//Gets the SDL_Window
		SDL_Window* getWindow();

		//Handles window events
		void handleEvent(SDL_Event& e);

		//Deallocates internals
		void free(void);

		//Window dimensions
		int getWidth(void);
		int getHeight(void);

		//Window focii
		bool hasMouseFocus(void);
		bool hasKeyboardFocus(void);
		bool isMinimized(void);

		//Window data
		const char* getTitle(void);

	private:
		//Window data
		SDL_Window* mWindow;
		char* mTitle;

		//Window dimensions
		int mWidth;
		int mHeight;

		//Window focus
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;

		SDL_Renderer* gRenderer;
};