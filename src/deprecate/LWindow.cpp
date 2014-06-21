#include "LWindow.h"
#include <sstream>
#include <string>

LWindow::LWindow(char* title, int width, int height)
{
	mTitle = title;
	//Initialize non-existant window
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = width;
	mHeight = height;
}

LWindow::~LWindow(void)
{
	free();
}

bool LWindow::init(void)
{
	//Create window
	mWindow = SDL_CreateWindow(mTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;

		gRenderer = createRenderer();
	}
	else
	{
		mWidth = 0;
		mHeight = 0;
	}

	return mWindow != NULL;
}

SDL_Renderer* LWindow::createRenderer(void)
{
	return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Renderer* LWindow::getRenderer(void)
{
	return gRenderer;
}

SDL_Window* LWindow::getWindow()
{
	return mWindow;
}

void LWindow::handleEvent(SDL_Event& e)
{
	//Window event occured
	if (e.type == SDL_WINDOWEVENT)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
			//Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(gRenderer);
			break;

			//Repaint on exposure
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(gRenderer);
			break;

			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}

		//Update window caption with new data
		/*if (updateCaption)
		{
			std::stringstream caption;
			caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}*/
	}
	//Enter exit full screen on return key
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
	{
		if (mFullScreen)
		{
			SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
			mFullScreen = false;
		}
		else
		{
			SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void LWindow::free(void)
{
	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth(void)
{
	return mWidth;
}

int LWindow::getHeight(void)
{
	return mHeight;
}

bool LWindow::hasMouseFocus(void)
{
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus(void)
{
	return mKeyboardFocus;
}

bool LWindow::isMinimized(void)
{
	return mMinimized;
}

const char* LWindow::getTitle(void)
{
	return SDL_GetWindowTitle(mWindow);;
}