#pragma once

#include <SDL.h>
#include "SDL_Application.h"

class SDL_Activity
{
	public:
		/*
		 * Instert description here
		 */
		SDL_Activity(void);
		~SDL_Activity(void);

		/*
		 * void
		*/

		/*
		 * param deltaTime - The number of ticks since the last update
		 * Called every frame, should be used to step update the activity
		*/
		virtual void updateDynamic(int deltaTime) = 0;

		/*
		* Called once every 1/60th of a second
		*/
		virtual void updateFixed(void) = 0;

		/*
		 * Called every frame, should be used to render the activity
		*/
		virtual void render(void) = 0;

		/*
		 * Called at the beginning of the activity, should be used as an opportunity to load assets
		*/
		virtual void init(void) = 0;

		/*
		 * Called at the end of the activity, should be used as an opportunity to dispose of all assets in the activity
		*/
		virtual void dispose(void) = 0;

		/*
		* param sdl_event - the SDL_Event that has occurred
		* Only called when a SDL event occurs, not every frame. Called before update and render if an event has occured.
		*/
		virtual void onEvent(SDL_Event& sdl_event) = 0;

		//Only needs to be overridden if using an opengl window
		virtual bool initGL(void);

		SDL_Application* getApp(void);
		void setApp(SDL_Application* app);

	private:
		SDL_Application* app;
};