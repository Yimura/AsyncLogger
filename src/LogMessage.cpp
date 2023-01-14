#include "LogMessage.hpp"
#include "LogLevel.hpp"

namespace base
{
    LogMessage::LogMessage(const eLogLevel level, std::source_location&& location, std::string&& message) :
        m_Level(level),
        m_Location(location),
        m_Message(message)
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

}