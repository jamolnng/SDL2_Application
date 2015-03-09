#pragma once
#include <fstream>

enum LogLevel
{
	LOG_OUTPUT,
	LOG_MESSAGE,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
};

class Logger
{
	public:
		Logger(bool separateErrorFile = false);
		~Logger(void);

		bool open(const char* file);
		bool output(const char* out);
		bool message(const char* message);
		bool warning(const char* warning);
		bool error(const char* error);
		/*
		Writing a fatal message should only be used when the program is going to exit after the message is written.
		Fatal closes the files after the message has been written making the logger useless.
		*/
		bool fatal(const char* fatal);
		bool custom(const char* customLogLevel, const char* custom);
		bool log(LogLevel level, const char* log);
		bool isOpen(void);
		bool close(void);

	private:
		bool write(const char* str);
		bool writeError(const char* str);
		bool separateErrorFile;
		std::ofstream file, errorFile;
};

extern Logger logger;