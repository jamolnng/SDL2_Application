#include "SDL_Activity.h"

SDL_Activity::SDL_Activity(void)
{
}

SDL_Activity::~SDL_Activity(void)
{
}

SDL_Application* SDL_Activity::getApp(void)
{
	return app;
}

void SDL_Activity::setApp(SDL_Application* app)
{
	if (this->app == nullptr) this->app = app;
}

bool SDL_Activity::initGL(void)
{
	return false;
}

Mouse SDL_Activity::getMouse(void)
{
	return mouse;
}

Keyboard SDL_Activity::getKeyboard(void)
{
	return keyboard;
}