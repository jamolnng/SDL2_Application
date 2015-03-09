#include "SDL_Utils.h"
#include "SDL_image.h"
#include <algorithm>
#include <ctime>

const char* SDL_Utils::readFile(const char* fileName)
{
	ifstream t(fileName);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	return str.c_str();
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
	SDL_Surface* surface = SDL_CreateRGBSurface(0, window->getWidth(), window->getHeight(), 24, rmask, gmask, bmask, amask);

	if (window->isUsingOpenGL())
	{
		glReadPixels(0, 0, window->getWidth(), window->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

		int index;
		void* temp_row;
		int height_div_2;
		temp_row = (void *)malloc(surface->pitch);
		if (NULL == temp_row)
		{
			SDL_SetError("Not enough memory for image inversion");
		}
		height_div_2 = (int)(surface->h * .5);
		for (index = 0; index < height_div_2; index++)
		{
			memcpy((Uint8 *)temp_row, (Uint8 *)(surface->pixels) + surface->pitch * index, surface->pitch);
			memcpy((Uint8 *)(surface->pixels) + surface->pitch * index, (Uint8 *)(surface->pixels) + surface->pitch * (surface->h - index - 1), surface->pitch);
			memcpy((Uint8 *)(surface->pixels) + surface->pitch * (surface->h - index - 1), temp_row, surface->pitch);
		}
		free(temp_row);
		//surface = flipVert(surface);
	}
	else
	{
		surface = SDL_GetWindowSurface(window->getWindow());
	}
	string file = string(fileName);
	string f1 = file;
	if (endsWith(toLower(f1), string(".png")))
	{
		IMG_SavePNG(surface, file.c_str());
	}
	else if (endsWith(toLower(f1), string(".bmp")))
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

int SDL_Utils::rand(void)
{
	srand((std::time(0) % std::rand()) * std::rand());
	return abs(std::rand());
}

string SDL_Utils::getDateTimeNow(void)
{
	std::time_t now = time(0);
	std::tm *local = localtime(&now);
	string rtime;
	string d = to_string(local->tm_mday);
	string m = to_string(1 + local->tm_mon);
	string y = to_string(1900 + local->tm_year);

	if (d.length() < 2) d = "0" + d;
	if (m.length() < 2) m = "0" + m;

	string hh = to_string(local->tm_hour);
	string mm = to_string(local->tm_min);
	string ss = to_string(local->tm_sec);

	if (hh.length() < 2) hh = "0" + hh;
	if (mm.length() < 2) mm = "0" + mm;
	if (ss.length() < 2) ss = "0" + ss;

	rtime.append(y).append("-").append(m).append("-").append(d).append("_");
	rtime.append(hh).append(".").append(mm).append(".").append(ss);
	return rtime;
}