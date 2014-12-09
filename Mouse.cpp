#include "Mouse.h"
#include <iostream>

using namespace std;

Mouse::Mouse(void)
{
	scrolldx = 1;
}

Mouse::~Mouse(void)
{
}

void Mouse::onEvent(SDL_Event& sdl_event)
{
	switch (sdl_event.type)
	{
		case SDL_MOUSEWHEEL:
			if (sdl_event.wheel.y > 0)
			{
				totalScroll += scrolldx;
				lastScroll = 1;
			}
			else if (sdl_event.wheel.y < 0)
			{
				totalScroll -= scrolldx;
				lastScroll = -1;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				if (int(sdl_event.button.button) == int(SDL_BUTTON_LEFT))
				{
					lmb = true;
					plmb = true;
				}
				if (int(sdl_event.button.button) == int(SDL_BUTTON_MIDDLE))
				{
					mmb = true;
					pmmb = true;
				}
				if (int(sdl_event.button.button) == int(SDL_BUTTON_RIGHT))
				{
					rmb = true;
					prmb = true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			{
				if (int(sdl_event.button.button) == int(SDL_BUTTON_LEFT))
				{
					lmb = false;
					plmb = false;
				}
				if (int(sdl_event.button.button) == int(SDL_BUTTON_MIDDLE))
				{
					mmb = false;
					pmmb = false;
				}
				if (int(sdl_event.button.button) == int(SDL_BUTTON_RIGHT))
				{
					rmb = false;
					prmb = false;
				}
				drag = false;
			}
			break;
		case SDL_MOUSEMOTION:
			mdelta = glm::vec2(sdl_event.motion.xrel, sdl_event.motion.yrel);
			mpos = glm::vec2(sdl_event.motion.x, sdl_event.motion.y);
			if (lmb || mmb || rmb)
			{
				drag = true;
			}
			break;
		case SDL_WINDOWEVENT:
			if (sdl_event.window.event == SDL_WINDOWEVENT_ENTER)
			{
				window = true;
			}
			if (sdl_event.window.event == SDL_WINDOWEVENT_LEAVE)
			{
				window = false;
			}
			break;
		default:
			break;
	}
}

void Mouse::clear(void)
{
	lastScroll = 0;
	plmb = pmmb = prmb = false;
	mdelta = glm::vec2(0, 0);
}

void Mouse::lock(bool locked)
{
	this->locked = locked;
	SDL_SetRelativeMouseMode(locked ? SDL_TRUE : SDL_FALSE);
}

bool Mouse::down(unsigned int button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			return lmb;
		case SDL_BUTTON_MIDDLE:
			return mmb;
		case SDL_BUTTON_RIGHT:
			return rmb;
		default:
			return false;
	}
}

bool Mouse::clicked(unsigned int button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			return plmb;
		case SDL_BUTTON_MIDDLE:
			return pmmb;
		case SDL_BUTTON_RIGHT:
			return prmb;
		default:
			return false;
	}
	return false;
}

bool Mouse::dragging(void)
{
	return drag;
}

int Mouse::scrollDirection(void)
{
	return lastScroll;
}

int Mouse::scroll(void)
{
	return totalScroll;
}

double Mouse::deltaX(void)
{
	return (double)mdelta.x;
}

double Mouse::deltaY(void)
{
	return (double)mdelta.y;
}

double Mouse::x(void)
{
	return (double)mpos.x;
}

double Mouse::y(void)
{
	return (double)mpos.y;
}

glm::vec2 Mouse::pos(void)
{
	return mpos;
}

glm::vec2 Mouse::delta(void)
{
	return mdelta;
}

void Mouse::setScrollAmount(unsigned int scrollAmount)
{
	scrolldx = scrollAmount;
}

bool Mouse::inWindow(void)
{
	return window;
}