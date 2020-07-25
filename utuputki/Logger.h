#ifndef LOGGER_H
#define LOGGER_H


#include <memory>

#include <fmt/core.h>


namespace utuputki {


class Config;


enum class LogLevel : unsigned int {
	  Debug
	, Info
	, Warning
	, Error
};


LogLevel parseLogLevel(const std::string &str);


class Logger {
	struct LoggerImpl;
	std::unique_ptr<LoggerImpl> impl;


	Logger()                               = delete;

	Logger(const Logger &other)            = delete;
	Logger &operator=(const Logger &other) = delete;

	Logger(Logger &&other)                 = delete;
	Logger &operator=(Logger &&other)      = delete;

public:

	explicit Logger(const Config &config);

	~Logger();

	static void message(LogLevel l, const std::string &str);

	template <typename... Args>
	static void message(LogLevel l, const char *format, const Args & ... args) {
		std::string str = fmt::format(format, args...);
		message(l, str);

	}
};


#define LOG_ERROR(...)    utuputki::Logger::message(utuputki::LogLevel::Error,   ##__VA_ARGS__)
#define LOG_WARNING(...)  utuputki::Logger::message(utuputki::LogLevel::Warning, ##__VA_ARGS__)
#define LOG_INFO(...)     utuputki::Logger::message(utuputki::LogLevel::Info,    ##__VA_ARGS__)
#define LOG_DEBUG(...)    utuputki::Logger::message(utuputki::LogLevel::Debug,   ##__VA_ARGS__)


}  // namespace utuputki


#endif  // LOGGER_H
