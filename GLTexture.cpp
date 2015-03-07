#include "GLTexture.h"
#include <cmath>

GLTexture::GLTexture(void)
{
	value = 0;
	surface = nullptr;
	glGenTextures(1, &value);
	pixels = nullptr;
}

GLTexture::GLTexture(char* file, int MIN_FILTER, int MAG_FILTER)
{
	value = 0;
	surface = nullptr;
	glGenTextures(1, &value);
	pixels = nullptr;
	load(file, MIN_FILTER, MAG_FILTER);
}

GLTexture::~GLTexture(void)
{
	dispose();
}

bool GLTexture::load(char* fileName, int MIN_FILTER, int MAG_FILTER)
{
	if (fileName == "") return 0;
	SDL_Surface* surface = IMG_Load(fileName);
	if (surface == 0)
	{
		return 0;
	}
	return load(surface, MIN_FILTER, MAG_FILTER);
}

bool GLTexture::load(SDL_Surface* surface, int MIN_FILTER, int MAG_FILTER)
{
	this->surface = surface;
	pitch = surface->pitch;
	width = surface->w;
	height = surface->h;
	pixels = surface->pixels;
	glBindTexture(GL_TEXTURE_2D, value);
	auto format = surface->format->Amask ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
	glBindTexture(GL_TEXTURE_2D, 0);
	return value != 0;
}

void GLTexture::dispose(void)
{
	if (surface != nullptr)
	{
		//SDL_FreeSurface(surface);
		surface = nullptr;
	}
	glDeleteTextures(1, &value);
}

void GLTexture::bind(void)
{
	glBindTexture(GL_TEXTURE_2D, value);
}

void GLTexture::unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int GLTexture::getWidth(void)
{
	return width;
}

unsigned int GLTexture::getHeight(void)
{
	return height;
}

unsigned int GLTexture::getPitch(void)
{
	return pitch;
}

void* GLTexture::getPixels(void)
{
	return pixels;
}

bool GLTexture::create(unsigned int width, unsigned int height, float r, float g, float b, float a, int MIN_FILTER, int MAG_FILTER)
{
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, (Uint8)std::round(r * 255.0f), (Uint8)std::round(g * 255.0f), (Uint8)std::round(b * 255.0f), (Uint8)std::round(a * 255.0f)));
	return load(surface, MIN_FILTER, MAG_FILTER);
}

bool GLTexture::create(unsigned int width, unsigned int height, void* pixels, int MIN_FILTER, int MAG_FILTER)
{
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 64, rmask, gmask, bmask, amask);
	return load(surface, MIN_FILTER, MAG_FILTER);
}

bool GLTexture::setPixels(void *pixels)
{
	if (value == 0 || pixels == nullptr || sizeof(pixels) != sizeof(getPixels())) return false;
	glBindTexture(GL_TEXTURE_2D, value);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->pixels = pixels;
	return true;
}

Uint32 GLTexture::getPixel(unsigned int x, unsigned int y)
{
	if (x >= width || y >= height) return 0;
	//Convert the pixels to 32 bit
	Uint32 *a = (Uint32*)surface->pixels;
	//Get the pixel requested
	return a[(y * (pitch/4)) + x];
}

bool GLTexture::testPixel(unsigned int x, unsigned int y)
{
	return getPixel(x, y) == 0 || getPixel(x, y) == 0xFFFFFF;
}

bool GLTexture::createEmpty(unsigned int width, unsigned int height, int MIN_FILTER, int MAG_FILTER)
{
	glBindTexture(GL_TEXTURE_2D, value);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

GLuint GLTexture::load(const char* fileName, int MIN_FILTER, int MAG_FILTER)
{
	GLuint out = 0;
	SDL_Surface* surface = IMG_Load(fileName);
	glGenTextures(1, &out);
	glBindTexture(GL_TEXTURE_2D, out);
	auto format = surface->format->Amask ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surface);
	return out;
}

SDL_Surface* GLTexture::loads(const char* fileName)
{
	return IMG_Load(fileName);
}