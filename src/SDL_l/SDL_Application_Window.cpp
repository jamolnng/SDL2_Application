#include <GL\glew.h>
#include "SDL_Application_Window.h"
#include <SDL_image.h>
#include "SDL_Activity.h"

SDL_Application_Window::SDL_Application_Window(bool useOpenGL, unsigned int openGLMajor, unsigned int openGLMinor)
{
	this->fullScreen = false;
	this->keyboardFocus = false;
	this->minimized = false;
	this->mouseFocus = false;
	this->sdl_renderer = 0;
	this->sdl_window = 0;
	this->useOpenGL = useOpenGL;
	this->openGLMajorVersion = openGLMajor;
	this->openGLMinorVersion = openGLMinor;
}

SDL_Application_Window::~SDL_Application_Window()
{
	dispose();
}

bool SDL_Application_Window::init(SDL_Activity* activity, char* title, unsigned int width, unsigned int height, Uint32 flags)
{
	this->title = title;
	this->width = width;
	this->height = height;
	if (useOpenGL) return initWithOpenGL(activity, flags);
	return initWithoutOpenGL(activity, flags);
}

bool SDL_Application_Window::initWithOpenGL(SDL_Activity* activity, Uint32 flags)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, openGLMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, openGLMinorVersion);
	sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | flags);
	if (sdl_window == 0)
	{
		width = 0;
		height = 0;
		return 0;
	}
	keyboardFocus = true;
	mouseFocus = true;
	/*sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (sdl_renderer != 0)*/
	{
		gl_context = SDL_GL_CreateContext(sdl_window);
		if (gl_context != 0)
		{
			glewExperimental = GL_TRUE;
			glewInit();
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

bool SDL_Application_Window::initWithoutOpenGL(SDL_Activity* activity, Uint32 flags)
{
	sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | flags);
	if (sdl_window != NULL)
	{
		mouseFocus = true;
		keyboardFocus = true;

		sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	else
	{
		width = 0;
		height = 0;
	}

	return sdl_window != NULL;
}

void SDL_Application_Window::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			width = e.window.data1;
			height = e.window.data2;
			if (isUsingOpenGL())
			{
				SDL_GL_SwapWindow(getWindow());
			}
			else
			{
				SDL_RenderPresent(sdl_renderer);
			}
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			if (isUsingOpenGL())
			{
				SDL_GL_SwapWindow(getWindow());
			}
			else
			{
				SDL_RenderPresent(sdl_renderer);
			}
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

void SDL_Application_Window::dispose(void)
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

SDL_Window *SDL_Application_Window::getWindow(void)
{
	return sdl_window;
}

SDL_Renderer *SDL_Application_Window::getRenderer(void)
{
	return sdl_renderer;
}

SDL_GLContext *SDL_Application_Window::getGLContext(void)
{
	return &gl_context;
}

int SDL_Application_Window::getWidth(void)
{
	return width;
}

int SDL_Application_Window::getHeight(void)
{
	return height;
}

const char* SDL_Application_Window::getTitle(void)
{
	title = (char*)SDL_GetWindowTitle(sdl_window);
	return title;
}

bool SDL_Application_Window::isFullscreen(void)
{
	return fullScreen;
}

bool SDL_Application_Window::isMinimized(void)
{
	return minimized;
}

bool SDL_Application_Window::hasKeyboardFocus(void)
{
	return keyboardFocus;
}

bool SDL_Application_Window::hasMouseFocus(void)
{
	return mouseFocus;
}

bool SDL_Application_Window::setFullscreen(bool fullscreenFlag)
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

void SDL_Application_Window::setIcon(char* iconFile)
{
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

void SDL_Application_Window::setTitle(char* title)
{
	this->title = title;
	SDL_SetWindowTitle(sdl_window, title);
}

bool SDL_Application_Window::isUsingOpenGL(void)
{
	return useOpenGL;
}

void SDL_Application_Window::setWidth(unsigned int width)
{
	this->width = width;
}

void SDL_Application_Window::setHeight(unsigned int height)
{
	this->height = height;
}