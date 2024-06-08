#pragma once
#include <source_location>
#include <string>
#include "LogLevel.hpp"
#include "LogStream.hpp"

namespace al
{
    class LogMessage
    {
    public:
        LogMessage(const eLogLevel level, std::chrono::system_clock::time_point&& timestamp, std::source_location&& location, std::string&& message, std::optional<std::shared_ptr<LogStream> const> stream);
        virtual ~LogMessage() = default;

        const eLogLevel& Level() const;
        const std::source_location& Location() const;
        const std::string& Message() const;
        const std::chrono::system_clock::time_point& Timestamp() const;
        const std::optional<std::shared_ptr<LogStream> const> Stream() const;

    private:
        const eLogLevel m_Level;
        const std::chrono::system_clock::time_point m_Timestamp;
        const std::source_location m_Location;
        const std::string m_Message;
        const std::optional<std::shared_ptr<LogStream> const> m_Stream;

    };
}