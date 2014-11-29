#pragma once

#include <SDL.h>
#include "glm\glm.hpp"

class Mouse
{
	public:
		Mouse(void);
		~Mouse(void);

		void onEvent(SDL_Event& sdl_event);
		void clear(void);
		void setScrollAmount(unsigned int scroll);
		void lock(bool locked);

		bool down(unsigned int button);
		bool clicked(unsigned int button);
		bool dragging(void);
		int scrollDirection(void);
		int scroll(void);
		double deltaX(void);
		double deltaY(void);
		double x(void);
		double y(void);
		glm::vec2 pos(void);
		glm::vec2 delta(void);

	private:
		bool lmb, mmb, rmb, drag, plmb, pmmb, prmb, locked;
		int lastScroll, totalScroll;
		unsigned int scrolldx;
		glm::vec2 mpos, mdelta;
};