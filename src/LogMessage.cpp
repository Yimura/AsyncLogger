#include "LogMessage.hpp"
#include "LogLevel.hpp"
#include <chrono>

namespace al
{
    LogMessage::LogMessage(const eLogLevel level, std::chrono::system_clock::time_point&& timestamp, std::source_location&& location, std::string&& message, std::optional<std::shared_ptr<LogStream> const> stream) :
        m_Level(level),
        m_Timestamp(timestamp),
        m_Location(location),
        m_Message(message),
        m_Stream(stream)
    {
        
    }

    const eLogLevel& LogMessage::Level() const
    {
        return m_Level;
    }

    const std::source_location& LogMessage::Location() const
    {
        return m_Location;
    }

    const std::string& LogMessage::Message() const
    {
        return m_Message;
    }

    const std::chrono::system_clock::time_point &LogMessage::Timestamp() const
    {
        return m_Timestamp;
    }

    const std::optional<std::shared_ptr<LogStream> const> LogMessage::Stream() const
    {
        return m_Stream;
    }
}