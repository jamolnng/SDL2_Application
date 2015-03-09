#include <GL\glew.h>
#include "SDL_Application.h"
#include "SDL_Activity.h"
#include "LTexture.h"
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <google/protobuf/stubs/common.h>

SDL_Application::SDL_Application(SDL_Activity* sdl_activity, bool useOpenGL, unsigned int openGLMajor, unsigned int openGLMinor) : activity(sdl_activity), window(useOpenGL, openGLMajor, openGLMinor), windowSurface(nullptr), exitCode(-1), running(false), exit(false), windowCreated(false)
{
	activity->setApp(this);
	initialized = false;
	maxUpdates = 5;
}

SDL_Application::~SDL_Application(void)
{
}

void SDL_Application::start(void)
{
	running = true;
	run();
}

void SDL_Application::end(void)
{
	running = false;
}

void SDL_Application::setExitCode(int newExitCode)
{
	exitCode = newExitCode;
}

bool SDL_Application::init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::string err("Could not initialize SDL @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::string err("Could not set render hint \"Scale Quality\" SDL @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
	{
		std::string err("Could not set render hint \"Vertical Sync\" SDL @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	if (!SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1"))
	{
		std::string err("Could not set render hint \"Framebuffer Acceleration\" SDL @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	return 1;
}

bool SDL_Application::isRunning(void)
{
	return running;
}

bool SDL_Application::isExiting(void)
{
	return exit;
}

bool SDL_Application::createWindow(char* title, unsigned int width, unsigned int height, Uint32 flags, char* iconFile)
{
	if (!window.init(activity, title, width, height, flags))
	{
		std::string err("Could not initialize window @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	renderer = window.getRenderer();
	if (!window.isUsingOpenGL()) if (renderer == nullptr || renderer == NULL)
	{
		std::string err("Could not create renderer @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::string err("Could not initialize SDL_Image library: ");
		err.append(IMG_GetError()).append(" @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.fatal(err.c_str());
		return 0;
	}
	window.setIcon(iconFile);
	if (!window.isUsingOpenGL())
	{
		SDL_SetRenderTarget(renderer, nullptr);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	else
	{
		glewExperimental = GL_TRUE;
		GLenum error;
		if ((error = glewInit()) != GLEW_OK)
		{
			logger.fatal((std::string("GLEW initialization: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(error)))).c_str());
			return 0;
		}
	}
	activity->init();
	return 1;
}

int SDL_Application::getExitCode(void)
{
	if (!exit) return -1;
	return exitCode;
}

int SDL_Application::finish(void)
{
	logger.close();
	if (!window.isUsingOpenGL()) SDL_DestroyRenderer(renderer);
	window.dispose();
	IMG_Quit();
	SDL_Quit();
	google::protobuf::ShutdownProtobufLibrary();
	return getExitCode();
}

SDL_Application_Window* SDL_Application::getWindow(void)
{
	return &window;
}

SDL_Surface* SDL_Application::loadImage(char* fileName)
{
	if (fileName == "" || fileName == NULL || fileName == nullptr)
	{
		std::string err("Cannot load image with a NULL file name @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.warning(err.c_str());
		return NULL;
	}
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(fileName);
	if (loadedSurface == nullptr)
	{
		std::string err("Could not load image @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.error(err.c_str());
		return NULL;
	}
	optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(window.getWindow())->format, 0);
	if (optimizedSurface == nullptr)
	{
		std::string err("Could not optimize image @ ");
		err.append(__FILE__).append(" ").append(std::to_string(__LINE__));
		logger.error(err.c_str());
		return NULL;
	}
	SDL_FreeSurface( loadedSurface );
	return optimizedSurface;
}

unsigned int frames = 0;
int fpsTime = 0;
unsigned int nextMaxUpdate = 5;

void SDL_Application::run(void)
{
	SDL_Event e;
	int updateNext = SDL_GetTicks();
	int updateTime = updateNext;
	int updateRate = (int)(1000.0f / 60.0f);
	int deltaTime = 0;
	int nextTime = updateNext;
	int updates = 0;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) end();
			window.handleEvent(e);
			activity->preEvent(e);
		}
		updates = 0;

		if (maxUpdates != nextMaxUpdate) maxUpdates = nextMaxUpdate;

		while ((updateTime - updateNext) >= updateRate && updates++ < (int)maxUpdates)
		{
			//fixed update
			activity->updateFixed();
			updateNext += updateRate;
		}
		if (updates >= (int)maxUpdates)
		{
			updateNext = updateTime;
		}
		activity->updateDynamic(deltaTime);

		if (window.isUsingOpenGL())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
		}

		activity->render();
		frames++;
		if ((updateTime - fpsTime) >= 1000)
		{
			_fps = (unsigned int)(((float)frames / (float)(updateTime - fpsTime)) * 1000.0f);
#ifdef _DEBUG
			printf("FPS: %i\n", _fps);
#endif
			frames = 0;
			fpsTime = 0;
			fpsTime = updateTime;
		}

		if (window.isUsingOpenGL())
		{
			SDL_GL_SwapWindow(window.getWindow());
		}
		else
		{
			SDL_RenderPresent(renderer);
		}
		activity->clear();

		updateTime = SDL_GetTicks();
		deltaTime = updateTime - nextTime;
		nextTime = updateTime;
	}
	activity->dispose();
	exit = true;
	running = false;
	if(exitCode == -1) setExitCode(0);
}

unsigned int SDL_Application::getFPS(void)
{
	return _fps;
}

bool SDL_Application::isInitialized(void)
{
	return initialized;
}

//Crypto SDL_Application::getCrypto(void)
//{
//	return crypto;
//}

void SDL_Application::setMaxUpdates(unsigned int max)
{
	if (max == 0) max = 5;
	nextMaxUpdate = max;
}