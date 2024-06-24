#pragma once
#include <chrono>
#include <source_location>
#include <sstream>
#include "LogLevel.hpp"
#include "LogStream.hpp"

namespace al
{
	class Logger;
	class LogCapture
	{
	public:
		LogCapture(const eLogLevel level, std::source_location&& location, std::optional<std::shared_ptr<LogStream> const> stream);
		~LogCapture();

		template<typename T>
		std::ostream& operator<< (const T& d);

	private:
		const eLogLevel m_Level;
		std::chrono::system_clock::time_point m_Timestamp;
		std::source_location m_Location;
		std::ostringstream m_Stream;
		std::optional<std::shared_ptr<LogStream> const> m_LogStream;
	};

	template<typename T>
	std::ostream& LogCapture::operator<< (const T& d)
	{
		m_Stream << d;
		return m_Stream;
	}

}