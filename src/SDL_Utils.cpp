#include "SDL_Utils.h"
#include "SDL_image.h"
#include <algorithm>

const char* SDL_Utils::readFile(const char* fileName)
{
	std::ifstream in(fileName);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	return contents.c_str();
}

bool SDL_Utils::saveScreenShot(SDL_Application_Window* window, const char* fileName)
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
	SDL_Surface* surface = SDL_CreateRGBSurface(0, window->getWidth(), window->getHeight(), 32, rmask, gmask, bmask, amask);

	if (window->isUsingOpenGL())
	{
		glReadBuffer(GL_FRONT);
		glReadPixels(0, 0, window->getWidth(), window->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		surface = flipVert(surface);
	}
	else
	{
		surface = SDL_GetWindowSurface(window->getWindow());
	}
	string file = string(fileName);
	if (endsWith(toLower(file), string(".png")))
	{
		IMG_SavePNG(surface, file.c_str());
	}
	else if (endsWith(toLower(file), string(".bmp")))
	{
		SDL_SaveBMP(surface, file.c_str());
	}
	else
	{
		file.append(".png");
		IMG_SavePNG(surface, file.c_str());
	}
	SDL_FreeSurface(surface);
	return false;
}

SDL_Surface* SDL_Utils::flipVert(SDL_Surface* sfc)
{
	SDL_Surface* result = SDL_CreateRGBSurface(sfc->flags, sfc->w, sfc->h, sfc->format->BytesPerPixel * 8, sfc->format->Rmask, sfc->format->Gmask, sfc->format->Bmask, sfc->format->Amask);
	unsigned char* pixels = (unsigned char*)sfc->pixels;
	unsigned char* rpixels = (unsigned char*)result->pixels;
	unsigned int pitch = sfc->pitch;
	unsigned int pxlength = pitch * sfc->h;
	if (result == nullptr) return nullptr;

	for (int line = 0; line < sfc->h; ++line)
	{
		unsigned int pos = line * pitch;
		rpixels[pos * pos + pitch] = pixels[(pxlength - pos) - pitch * pxlength - pos];
	}

	return result;
}

string SDL_Utils::toLower(string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

bool SDL_Utils::endsWith(string& full, string& end)
{
	if (full.length() >= end.length())
	{
		return (0 == full.compare(full.length() - end.length(), end.length(), end));
	}
	else
	{
		return false;
	}
}