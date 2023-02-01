/** \file log.h */
#pragma once

#include "systems/system.h"
#include <spdlog/spdlog.h>

namespace Engine 
{
	/** class Log -  Console & File Logging */
	class Log : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the system

		template<class  ...Args>
		static void debug(Args&&... args);

		template<class  ...Args>
		static void error(Args&&... args);

		template<class  ...Args>
		static void file(Args&&... args);

		template<class  ...Args>
		static void info(Args&&... args);

		template<class  ...Args>
		static void release(Args&&... args);

		template<class  ...Args>
		static void trace(Args&&... args);

		template<class  ...Args>
		static void warn(Args&&... args);

	private:
		static std::shared_ptr<spdlog::logger> consoleLogger; //!< Console Logger
		static std::shared_ptr<spdlog::logger> fileLogger; //!< File Logger
	};

	template<class  ...Args>
	static void Log::debug(Args&&... args)
	{
#ifdef NG_DEBUG
		consoleLogger->debug(std::forward<Args>(args) ...);
#endif
	}

	template<class  ...Args>
	static void Log::error(Args&&... args)
	{
#ifdef NG_DEBUG
		consoleLogger->error(std::forward<Args>(args) ...);
#endif
	}

	template<class  ...Args>
	static void Log::file(Args&&... args)
	{
		if(fileLogger) consoleLogger->trace(std::forward<Args>(args) ...);
	}

	template<class  ...Args>
	static void Log::info(Args&&... args)
	{
#ifdef NG_DEBUG
		consoleLogger->info(std::forward<Args>(args) ...);
#endif
	}

	template<class  ...Args>
	static void Log::release(Args&&... args)
	{
#ifdef NG_DEBUG
	consoleLogger->release(std::forward<Args>(args) ...);
#endif
	}

	template<class  ...Args>
	static void Log::trace(Args&&... args)
	{
#ifdef NG_DEBUG
		consoleLogger->trace(std::forward<Args>(args) ...);
#endif
	}

	template<class  ...Args>
	static void Log::warn(Args&&... args)
	{
#ifdef NG_DEBUG
		consoleLogger->warn(std::forward<Args>(args) ...);
#endif
	}
}
