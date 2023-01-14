#include "LogCapture.hpp"
#include "Logger.hpp"

namespace base
{
    LogCapture::LogCapture(const eLogLevel level, std::source_location&& location) :
        m_Level(level),
        m_Location(location)
    {

    }

    LogCapture::~LogCapture()
    {
        m_Stream << '\n';
        Logger::PushMessage(m_Level, std::move(m_Location), std::move(m_Stream.str()));
    }
}