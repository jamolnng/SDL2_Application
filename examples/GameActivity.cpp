#pragma once

#include "GameActivity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

GameActivity::GameActivity(void) : world(this, b2Vec2(0, -9.80665f))
{
}

GameActivity::~GameActivity(void)
{
}

void GameActivity::init(void)
{
	world.init();
}

void GameActivity::updateDynamic(int deltaTime)
{
	//world.update(deltaTime);
}

void GameActivity::updateFixed(void)
{
	world.update();
}

void GameActivity::render(void)
{
	world.render();
}

void GameActivity::dispose(void)
{
	world.dispose();
}

void GameActivity::onEvent(SDL_Event& sdl_event)
{
	if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_ESCAPE)
	{
		getApp()->end();
	}
	if (sdl_event.type == SDL_WINDOWEVENT)
	{
		if (sdl_event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			int w = getApp()->getWindow()->getWidth();
			int h = getApp()->getWindow()->getHeight();
			if (getApp()->getWindow()->isUsingOpenGL())
			{
				glViewport(0, 0, w, h);
				glMatrixMode(GL_PROJECTION);
				/*glLoadIdentity();
				gluOrtho2D(0, w, h, 0);*/
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
			}
		}
	}
	world.onEvent(sdl_event);
}

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

	return 1;
}