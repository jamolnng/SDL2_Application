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
				if ((int)sdl_event.button.button == SDL_BUTTON_LEFT)
				{
					lmb = true;
					plmb = true;
				}
				if ((int)sdl_event.button.button == SDL_BUTTON_MIDDLE)
				{
					mmb = true;
					pmmb = true;
				}
				if ((int)sdl_event.button.button == SDL_BUTTON_RIGHT)
				{
					rmb = true;
					prmb = true;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if ((int)sdl_event.button.button == SDL_BUTTON_LEFT)
			{
				lmb = false;
				plmb = false;
			}
			if ((int)sdl_event.button.button == SDL_BUTTON_MIDDLE)
			{
				mmb = false;
				pmmb = false;
			}
			if ((int)sdl_event.button.button == SDL_BUTTON_RIGHT)
			{
				rmb = false;
				prmb = false;
			}
			drag = false;
			break;
		case SDL_MOUSEMOTION:
			mdelta = glm::vec2(sdl_event.motion.x - mpos.x, sdl_event.motion.y - mpos.y);
			mpos = glm::vec2(sdl_event.motion.x, sdl_event.motion.y);
			if (lmb || mmb || rmb)
			{
				drag = true;
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
}

void Mouse::lock(bool locked)
{
	SDL_SetRelativeMouseMode(locked ? SDL_TRUE : SDL_FALSE);
}

bool Mouse::down(unsigned int button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			return lmb;
			break;
		case SDL_BUTTON_MIDDLE:
			return mmb;
			break;
		case SDL_BUTTON_RIGHT:
			return rmb;
			break;
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
			break;
		case SDL_BUTTON_MIDDLE:
			return pmmb;
			break;
		case SDL_BUTTON_RIGHT:
			return prmb;
			break;
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

int Mouse::deltaX(void)
{
	return (int)mdelta.x;
}

int Mouse::deltaY(void)
{
	return (int)mdelta.y;
}

int Mouse::x(void)
{
	return (int)mpos.x;
}

int Mouse::y(void)
{
	return (int)mpos.y;
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