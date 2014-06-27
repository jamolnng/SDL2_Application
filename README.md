SDL2_Application
================

SDL2 Application is a small, easy to use, library for SDL2, SDL2_image, and glew. The library focuses mostly around OpenGL.

Some things this library includes:
- Window handling and the option to use OpenGL rendering over SDL rendering
- Refined event handling
- Pre-Built run loop with options for both fixed and dynamic updating
- Full classes for OpenGL texutures, shaders, vertexbuffer objects, and framebuffer objects (more to come)
- Full classes for SDL textures
- A interface class to run your game through (SDL_Activity)

Here is a

full working example application that uses Box2D https://github.com/jamolnng/Open-Source/tree/master/SDL_App_Box2D_Test

and an

Example of a basic application:

main.cpp
```cpp
#include "GameActivity.h"
#include <SDL.h>
#include <SDL_Application.h>

int main(int arg, char* args[])
{
	GameActivity game;
	SDL_Application app(&game, true /*Use OpenGL*/, 2 /*OpenGL Major Version*/, 1 /*OpenGL Minor Version*/);
	if (app.init())
	{
		if (app.createWindow("SDL2 Application Test", 854, 500, SDL_WINDOW_RESIZABLE))
		{
			app.start();
		}
	}
	return app.finish();
}
```

GameActivity.h
```cpp
#pragma once
#include <SDL_Activity.h>

class GameActivity : public SDL_Activity
{
	public:
		GameActivity(void);
		~GameActivity(void);

		void updateDynamic(int deltaTime);
		//Called every 1/60th of a second
		void updateFixed(void);

		void render(void);

		void init(void);

		void dispose(void);

		void onEvent(SDL_Event& sdl_event);
		
		//Only needs to be overriden if you explicitly say to use OpenGL otherwise you do not need the function
		bool initGL(void);
};
```

GameActivity.cpp
```cpp
#include "GameActivity.h"

GameActivity::GameActivity(void)
{
}

GameActivity::~GameActivity(void)
{
}

void GameActivity::updateDynamic(int deltaTime)
{
}

void GameActivity::updateFixed(void)
{
}

void GameActivity::render(void)
{
}

void GameActivity::init(void)
{
}

void GameActivity::dispose(void)
{
}

void GameActivity::onEvent(SDL_Event& sdl_event)
{
	if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_ESCAPE)
	{
		getApp()->end();
	}
}

//Only needs to be overriden if you explicitly say to use OpenGL otherwise you do not need the function
bool GameActivity::initGL(void)
{
	int w = getApp()->getWindow()->getWidth();
	int h = getApp()->getWindow()->getHeight();

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT, GL_FILL);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return true;
}
```
