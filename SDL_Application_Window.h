#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

class SDL_Activity;

class SDL_Application_Window
{
	public:
		SDL_Application_Window(bool useOpenGL = false, unsigned int openGLMajor = 2, unsigned int openGLMinor = 1);
		~SDL_Application_Window(void);

		bool init(SDL_Activity* activity, char* title = "SDL Layout Window", unsigned int width = 854, unsigned int height = 500, Uint32 flags = SDL_WINDOW_SHOWN);

		void handleEvent(SDL_Event& e);
		void dispose(void);

		SDL_Window* getWindow(void);
		SDL_Renderer* getRenderer(void);
		SDL_GLContext* getGLContext(void);

		int getWidth(void), getHeight(void);
		void setWidth(unsigned int), setHeight(unsigned int);
		const char* getTitle(void);
		bool hasMouseFocus(void), hasKeyboardFocus(void), isFullscreen(void), isMinimized(void), isUsingOpenGL(void);

		bool setFullscreen(bool fullscreen, bool useCurrentDisplayMode = true);
		void setIcon(char* iconFile = "");
		void setTitle(char* title = "");

	private:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;
		SDL_GLContext gl_context;

		int width, height;
		char* title;
		bool mouseFocus, keyboardFocus, fullScreen, minimized;
		bool useOpenGL;
		int openGLMajorVersion, openGLMinorVersion;

		bool initWithOpenGL(SDL_Activity* activity, Uint32 flags);
		bool initWithoutOpenGL(SDL_Activity* activity, Uint32 flags);
};

