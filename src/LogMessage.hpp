#pragma once
#include <source_location>
#include <string>
#include "LogLevel.hpp"

namespace base
{
    class LogMessage
    {
    public:
        LogMessage(const eLogLevel level, std::source_location&& location, std::string&& message);
        virtual ~LogMessage() = default;

        const eLogLevel& Level() const;
        const std::source_location& Location() const;
        const std::string& Message() const;

    private:
        const eLogLevel m_Level;
        const std::source_location m_Location;
        const std::string m_Message;

    };
}