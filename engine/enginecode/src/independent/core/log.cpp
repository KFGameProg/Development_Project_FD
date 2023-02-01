/**\ file log.cpp */
#include "engine_pch.h"
#include "core/log.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Log::consoleLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::fileLogger = nullptr;

	/** Set Logger system */
	void Log::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		spdlog::set_level(spdlog::level::trace);

		consoleLogger = spdlog::stdout_color_mt("Console");

		char filepath[256] = "logs/";
		char time[128];

		//try {
		//	std::time_t t = std::time(nullptr);
		//	std::strftime(time, sizeof(time), "%d_%m_%y I_%M_%S", std::localtime(&t)); //!< Formatting Current Time into time string
		//	strcat_s(filepath, time);
		//	strcat_s(filepath, ".txt");

		//	s_fileLogger = spdlog::basic_logger_mt("File", filepath);
		//}
		//catch (const spdlog::spdlog_ex& e) {
		//	s_consoleLogger->error("Could not start file logger: {0}", e.what());	//!< Error Logging
		//	s_fileLogger.reset();
		//}
	}
	void Log::stop(SystemSignal close, ...)
	{
		consoleLogger->info("Stopping Console Logger");
		consoleLogger.reset();
	}
}
