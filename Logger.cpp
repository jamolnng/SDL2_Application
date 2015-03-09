#include "Logger.h"
#include <iostream>
#include <string>
#include "SDL_Utils.h"

Logger logger = Logger(true);

Logger::Logger(bool separateErrorFile)
{
	this->separateErrorFile = separateErrorFile;
}

Logger::~Logger(void)
{
}

bool Logger::write(const char* str)
{
	if (!isOpen()) return false;
	string td = SDL_Utils::getDateTimeNow();
	file << td.c_str() << " " << str << "\n";
#ifdef _DEBUG
	std::cout << str << std::endl;
#endif
	return true;
}

bool Logger::writeError(const char* str)
{
	if (!isOpen()) return false;
	string td = SDL_Utils::getDateTimeNow();
	errorFile << td.c_str() << " " << str << "\n";
#ifdef _DEBUG
	std::cout << str << std::endl;
#endif
	return true;
}

bool Logger::open(const char* file)
{
	this->file.open(file, std::ios::out | std::ios::trunc);
	if (separateErrorFile)
	{
		if (!this->file.is_open()) return false;
		std::string sfile(file);
		unsigned int lastPeriod = sfile.find_last_of('.');
		unsigned int lastBSlash = sfile.find_last_of('\\');
		unsigned int lastFSlash = sfile.find_last_of('/');
		if (lastBSlash != std::string::npos && lastPeriod < lastBSlash) return false;
		if (lastFSlash != std::string::npos && lastPeriod < lastFSlash) return false;
		if (lastPeriod == std::string::npos) sfile = sfile.append(".err");
		else sfile = sfile.substr(0, sfile.find_last_of('.')).append(".err");
		this->errorFile.open(sfile.c_str(), std::ios::out | std::ios::trunc);
	}
	return isOpen();
}

bool Logger::output(const char* out)
{
	return log(LOG_OUTPUT, out);
}

bool Logger::message(const char* message)
{
	return log(LOG_MESSAGE, message);
}

bool Logger::warning(const char* warning)
{
	return log(LOG_WARNING, warning);
}

bool Logger::error(const char* error)
{
	return log(LOG_ERROR, error);
}

bool Logger::fatal(const char* fatal)
{
	return log(LOG_FATAL, fatal);
}

bool Logger::custom(const char* customLogLevel, const char* custom)
{
	if (!isOpen()) return false;
	if (customLogLevel == NULL || customLogLevel == nullptr || customLogLevel == "")
	{
		return write(string(custom).c_str());
	}
	else
	{
		return write((string(customLogLevel) + " " + string(custom)).c_str());
	}
}

bool Logger::log(LogLevel level, const char* log)
{
	if (!isOpen()) return false;
	switch (level)
	{
		case LOG_OUTPUT:
			return write(("Output:  " + string(log)).c_str());
			break;
		case LOG_MESSAGE:
			return write(("Message: " + string(log)).c_str());
			break;
		case LOG_WARNING:
			return write(("Warning: " + string(log)).c_str());
			break;
		case LOG_ERROR:
			return separateErrorFile ? writeError(("Error:   " + string(log)).c_str()) : write(("Error:   " + string(log)).c_str());
			break;
		case LOG_FATAL:
		{
			bool success = (separateErrorFile ? writeError(("Fatal:   " + string(log)).c_str()) : write(("Fatal:   " + string(log)).c_str()));
#ifdef _DEBUG
			system("PAUSE");
#endif
			return close() && success;
			break;
		}
		default:
			return write(("Unknown: " + string(log)).c_str());
			break;
	}
}

bool Logger::isOpen(void)
{
	return file.is_open() && (separateErrorFile ? errorFile.is_open() : true);
}

bool Logger::close(void)
{
	file.close();
	if (separateErrorFile) errorFile.close();
	return !isOpen();
}