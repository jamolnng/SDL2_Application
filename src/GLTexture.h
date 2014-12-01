#pragma once

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "GLObject.h"
#include "SDL_Application.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Crypto.h"

class GLTexture : public GLObject<GLuint>
{
	public:
		GLTexture(void);
		GLTexture(char* file, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		~GLTexture(void);

		bool load(char* fileName, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		bool load(SDL_Surface* surface, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		bool create(unsigned int width, unsigned int height, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		bool create(unsigned int width, unsigned int height, void* pixels, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		bool createEmpty(unsigned int width, unsigned int height, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		void dispose(void);
		void bind(void);
		void unbind(void);
		
		unsigned int getWidth(void);
		unsigned int getHeight(void);
		unsigned int getPitch(void);

		void* getPixels(void);
		bool setPixels(void* pixels);

		Uint32 getPixel(unsigned int x, unsigned int y);
		bool testPixel(unsigned int x, unsigned int y);

		SDL_Surface* getSurface(void);

		static GLuint load(const char* fileName, int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR);
		static SDL_Surface* loads(const char* fileName);

	private:
		SDL_Surface* surface;
		void* pixels;
		unsigned int width, height, pitch;
};