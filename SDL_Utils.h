#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include "SDL_Application.h"

#ifndef DLLDIR
#ifdef DLLDIR_EX
#define DLLDIR  __declspec(dllexport)   // export DLL information
#else
#define DLLDIR  __declspec(dllimport)   // import DLL information
#endif
#endif

using std::string;
using std::ifstream;

class SDL_Utils
{
	public:
		static const char* readFile(const char* fileName);
		static bool saveScreenShot(SDL_Application_Window* window, const char* fileName);
		static SDL_Surface* flipVert(SDL_Surface* surfaceToFlip);
		static string toLower(string&);
		static bool endsWith(string& fullString, string& ending);
		static int rand(void);
		/*
		 Returns current date and time (YYYY-mm-dd_hh.mm.ss)
		*/
		static string getDateTimeNow(void);
};