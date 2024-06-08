#pragma once
#include "LogIntermediate.hpp"

namespace al
{
    class LogStream
    {
    public:
        LogStream(std::string name, void* userData = nullptr);
        
        const std::string& Name() const;
        const void* UserData() const;
        bool Enabled() const;

        void SetEnabled(bool state);

    private:
        std::string m_Name;
        void* m_UserData;
        bool m_Enabled;

    };
}