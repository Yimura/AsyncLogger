#include "LogIntermediate.hpp"

namespace al
{
    LogIntermediate::LogIntermediate(const std::string_view formatString, const std::source_location location) :
        m_FormatString(formatString),
        m_Location(location)
    {
        
    }

    LogIntermediate::LogIntermediate(const char* formatString, const std::source_location location) :
        m_FormatString(formatString),
        m_Location(location)
    {

    }

    LogIntermediate::LogIntermediate(const std::string &formatString, const std::source_location location) :
        m_FormatString(formatString),
        m_Location(location)
    {

    }

    const std::string_view LogIntermediate::FormatString() const
    {
        return m_FormatString;
    }

    std::source_location&& LogIntermediate::Location()
    {
        return std::move(m_Location);
    }
}
