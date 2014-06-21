#include "GLWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_Activity.h"

GLWindow::GLWindow(char* title, int width, int height, char* iconFile)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->fullScreen = false;
	this->keyboardFocus = false;
	this->minimized = false;
	this->mouseFocus = false;
	this->sdl_renderer = 0;
	this->sdl_window = 0;
	if (iconFile != "")
	{
		SDL_Surface *surface;
		if ((surface = IMG_Load(iconFile)) != NULL)
		{
			SDL_SetWindowIcon(sdl_window, surface);
			SDL_FreeSurface(surface);
			surface = NULL;
		}
	}
}

GLWindow::~GLWindow(void)
{
	dispose();
}

bool GLWindow::init(SDL_Activity* activity)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (sdl_window == 0)
	{
		width = 0;
		height = 0;
		return 0;
	}
	keyboardFocus = true;
	mouseFocus = true;
	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl_renderer != 0)
	{
		gl_context = SDL_GL_CreateContext(sdl_window);
		if (gl_context != 0)
		{
			if (!(SDL_GL_SetSwapInterval(1) < 0))
			{
				if (activity->initGL())
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void GLWindow::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			width = e.window.data1;
			height = e.window.data2;
			SDL_RenderPresent(sdl_renderer);
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(sdl_renderer);
			break;

			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			mouseFocus = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mouseFocus = false;
			break;

			//Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true;
			break;

			//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocus = false;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			minimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			minimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			minimized = false;
			break;
		}
	}
}

void GLWindow::dispose(void)
{
	if (sdl_window != 0)
	{
		SDL_DestroyWindow(sdl_window);
	}

	this->width = 0;
	this->height = 0;
	this->fullScreen = false;
	this->keyboardFocus = false;
	this->minimized = false;
	this->mouseFocus = false;
	this->sdl_renderer = 0;
	this->sdl_window = 0;
}

SDL_Window *GLWindow::getWindow(void)
{
	return sdl_window;
}

SDL_Renderer *GLWindow::getRenderer(void)
{
	return sdl_renderer;
}

int GLWindow::getWidth(void)
{
	return width;
}

int GLWindow::getHeight(void)
{
	return height;
}

const char* GLWindow::getTitle(void)
{
	title = (char*)SDL_GetWindowTitle(sdl_window);
	return title;
}

bool GLWindow::isFullscreen(void)
{
	return fullScreen;
}

bool GLWindow::isMinimized(void)
{
	return minimized;
}

bool GLWindow::hasKeyboardFocus(void)
{
	return keyboardFocus;
}

bool GLWindow::hasMouseFocus(void)
{
	return mouseFocus;
}

bool GLWindow::setFullscreen(bool fullscreenFlag)
{
	if (fullScreen == fullscreenFlag) return 0;
	int i = -1;
	if (isFullscreen())
	{
		fullScreen = false;
		i = SDL_SetWindowFullscreen(sdl_window, SDL_FALSE);
	}
	else
	{
		fullScreen = true;
		minimized = false;
		i = SDL_SetWindowFullscreen(sdl_window, SDL_TRUE);
	}
	return i >= 0;
}