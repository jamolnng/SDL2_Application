#pragma once

#include <SDL.h>
#include "SDL_Application_Window.h"

class SDL_Activity;

class SDL_Application
{
	public:
		/*
		 * param activity - The activity that is run
		 * Instert description here
		*/
		SDL_Application(SDL_Activity* activity, bool useOpenGL, unsigned int openGLMajor = 2, unsigned int openGLMinor = 1);
		~SDL_Application(void);

		/*
		* void
		*/

		/*
		* Starts the game in its game loop
		*/
		void start(void);

		/*
		* Prepares to exit the game loop and end the windows process
		*/
		void end(void);

		/*
		 * Sets the exit code of the process
		*/
		void setExitCode(int);

		/*
		* bool
		*/

		/*
		 * Initialises SDL, OpenGL, and the game, should only be called once
		 * Returns true if fully initialised
		*/
		bool init(void);

		/*
		* Returns true if the game is running inside of the run loop
		*/
		bool isRunning(void);

		/*
		* Returns true if the game is in the works of exiting
		*/
		bool isExiting(void);

		/*
		 * char* windowTitle - The displayed title of the window
		 * unsigned int width - The width of the window
		 * unsigned int height - The height of the window
		* Returns true if the game window is successfully created, if the window has already been created it returns false
		*/
		bool createWindow(char* title = "SDL Layout Window", unsigned int width = 854, unsigned int height = 500, Uint32 flags = SDL_WINDOW_SHOWN, char* iconFile = "");

		/*
		* Int
		*/

		/*
		 * If the game is not exiting (the exit bool is equal to false) it returns -1
		 * Returns the integer value of the variable exitCode which is the exit code for the entire Windows process
		*/
		int getExitCode(void);

		/*
		* The finish method contains all final calls to SDL and is the last method called before the window process exits
		* Returns the final exit code for the game
		*/
		int finish(void);

		/*
		* Game Objects
		*/
		SDL_Application_Window* getWindow(void);

		SDL_Surface* loadImage(char* fileName = "");

		unsigned int getFPS(void);

	private:
		/*
		* void
		*/

		/*
		* The run method for the entire game
		*/
		void run(void);

		/*
		* bool
		*/

		/*
		 * Bool that describes if the game is in the run loop
		*/
		bool running;

		/*
		* Bool that describes if the game is preparing to exit
		*/
		bool exit;

		/*
		* Bool that describes if the game window has been created
		*/
		bool windowCreated;

		/*
		* Int
		*/

		/*
		 * The exit code of the windows process, only used at the very end of the process
		*/
		int exitCode;

		/*
		 * Game Objects
		*/

		//The actual game window
		SDL_Application_Window window;

		//The surface in which we render to the window
		SDL_Surface *windowSurface;

		//The activity that is run
		SDL_Activity *activity;

		//The game renderer
		SDL_Renderer* renderer;

		//FPS var
		unsigned int _fps;
};