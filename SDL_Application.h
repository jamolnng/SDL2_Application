#pragma once

#include <SDL.h>
#include "SDL_Application_Window.h"
#include "Properties.pb.h"
#include "Crypto.h"

class SDL_Activity;

class SDL_Application
{
	public:
		/*
		* param activity - The activity that is run
		* param useOpenGL - Override SDL rendering and just use OpenGL (this means you can't use SDL rendering classes)
		* param openGLMajor - The major version of OpenGL (for example 4 to use OpenGL 4.X, where X is the minor version)
		* param OpenGLMinor - The minor version of OpenGL (for example 2 to use OpenGL X.2, where X is the major version)
		*/
		SDL_Application(SDL_Activity* activity, bool useOpenGL, unsigned int openGLMajor = 2, unsigned int openGLMinor = 1);
		SDL_Application(SDL_Activity* activity, Properties props);
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
		* Sets the exit code of the process, only use this if you know what you are doing
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

		bool createWindow(Properties props);

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

		/*
		* Loads an image into a SDL_Surface from the file name
		* NOTE: the file name is from the path the .exe is located in
		*/
		SDL_Surface* loadImage(char* fileName = "");

		/*
		* Returns how many frames are being rendered each second
		*/
		unsigned int getFPS(void);

		/*
		 * Returns the static update run time
		 */
		float getStaticTime(void);

		/*
		 * Returns the dynamic update run time
		 */
		unsigned int getDynamicTime(void);

		/*
		* Returns if the SDL_Application has been initialized
		*/
		bool isInitialized(void);

		/*
		 * Returns the optional properties
		*/
		Properties getProperties(void);

		/*
		 * Returns the default crypto class
		 */
		Crypto getCrypto(void);

	private:
		/*
		* void
		*/

		//The run method for the entire game
		void run(void);

		/*
		* bool
		*/
		
		//Bool that describes if the game is in the run loop
		bool running;

		
		//Bool that describes if the game is preparing to exit
		bool exit;

		
		//Bool that describes if the game window has been created
		bool windowCreated;

		//boolean if the application has been initialized
		bool initialized;

		/*
		* Int
		*/
		
		//The exit code of the windows process, only used at the very end of the process/
		int exitCode;

		//The static update running time
		float staticTime;

		//The dynamic update running time
		unsigned int dynamicTime;

		//FPS var
		unsigned int _fps;

		/*
		 * Objects
		*/

		//The actual game window
		SDL_Application_Window window;

		//The surface in which we render to the window
		SDL_Surface *windowSurface;

		//The activity that is run
		SDL_Activity *activity;

		//The game renderer
		SDL_Renderer* renderer;

		//Optional properties
		Properties properties;

		//Default encryptor/decryptor
		Crypto crypto;
};