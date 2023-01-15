#pragma once
#include <source_location>
#include <string_view>

namespace al
{
    class LogIntermediate
    {
    public:
        LogIntermediate(const std::string_view formatString, const std::source_location location = std::source_location::current());
        LogIntermediate(const char* formatString, const std::source_location location = std::source_location::current());
        LogIntermediate(const std::string& formatString, const std::source_location location = std::source_location::current());
        virtual ~LogIntermediate() = default;

        const std::string_view FormatString() const;
        std::source_location&& Location();

    private:
        const std::string_view m_FormatString;
        std::source_location m_Location;

    };
}