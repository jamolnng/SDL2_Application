#include <GL\glew.h>
#include "SDL_Application.h"
#include "SDL_Activity.h"
#include "LTexture.h"
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

SDL_Application::SDL_Application(SDL_Activity* sdl_activity, bool useOpenGL, unsigned int openGLMajor, unsigned int openGLMinor) : activity(sdl_activity), window(useOpenGL, openGLMajor, openGLMinor), windowSurface(nullptr), exitCode(-1), running(false), exit(false), windowCreated(false)
{
	activity->setApp(this);
	initialized = false;
}

SDL_Application::SDL_Application(SDL_Activity* sdl_activity, Properties props) : activity(sdl_activity), window(props.getb("UseOpenGL"), props.geti("OpenGLMajor"), props.geti("OpenGLMinor")), windowSurface(nullptr), exitCode(-1), running(false), exit(false), windowCreated(false)
{
	activity->setApp(this);
	initialized = false;
	properties = props;
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
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 0;
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) return 0;
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
	if (!window.init(activity, title, width, height, flags)) return 0;
	renderer = window.getRenderer();
	if (!window.isUsingOpenGL()) if (renderer == nullptr) return 0;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return 0;
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
			fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
			system("pause");
			return 0;
		}
	}
	activity->init();
	return 1;
}

bool SDL_Application::createWindow(Properties props)
{
	string title = props.gets("Title");
	int width = props.geti("Width");
	int height = props.geti("Height");
	Uint32 flags = props.geti("Flags");
	string icon = props.gets("Icon");

	return createWindow((char*)title.c_str(), width, height, flags, (char*)icon.c_str());
}

int SDL_Application::getExitCode(void)
{
	if (!exit) return -1;
	return exitCode;
}

int SDL_Application::finish(void)
{
	if (!exit) return -1;
	if (!window.isUsingOpenGL()) SDL_DestroyRenderer(renderer);
	window.dispose();
	IMG_Quit();
	SDL_Quit();
	return getExitCode();
}

SDL_Application_Window* SDL_Application::getWindow(void)
{
	return &window;
}

SDL_Surface* SDL_Application::loadImage(char* fileName)
{
	if (fileName == "") return 0;
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(fileName);
	if( loadedSurface == nullptr ) return 0;
	optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(window.getWindow())->format, 0);
	if (optimizedSurface == nullptr) return 0;
	SDL_FreeSurface( loadedSurface );
	return optimizedSurface;
}

unsigned int frames = 0;
int fpsTime = 0;

void SDL_Application::run(void)
{
	SDL_Event e;
	int updateNext = SDL_GetTicks();
	int updateTime = updateNext;
	int updateRate = (int)(1000.0f / 60.0f);
	int deltaTime = 0;
	int nextTime = updateNext;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) end();
			window.handleEvent(e);
			activity->preEvent(e);
		}

		int updates = 0;
		updateTime = SDL_GetTicks();

		while ((updateTime - updateNext) >= updateRate && updates++ < 5)
		{
			//fixed update
			staticTime += updateRate;
			activity->updateFixed();
			updateNext += updateRate;
		}

		if (updates == 5 && (updateTime - updateNext) >= updateRate)
		{
			printf("The Program Can't Keep Up\n");
		}
		dynamicTime += deltaTime;
		activity->updateDynamic(deltaTime);

		if (window.isUsingOpenGL())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		deltaTime = SDL_GetTicks() - nextTime;
		nextTime = SDL_GetTicks();
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

Properties SDL_Application::getProperties(void)
{
	return properties;
}

float SDL_Application::getStaticTime(void)
{
	return staticTime;
}

unsigned int SDL_Application::getDynamicTime(void)
{
	return dynamicTime;
}

Crypto SDL_Application::getCrypto(void)
{
	return crypto;
}