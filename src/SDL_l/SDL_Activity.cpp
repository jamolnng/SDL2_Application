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
	if (this->app == NULL) this->app = app;
}

bool SDL_Activity::initGL(void)
{
	return false;
}