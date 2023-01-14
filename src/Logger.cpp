#include "Logger.hpp"
#include "LogCapture.hpp"
#include "LogMessage.hpp"

namespace base
{
    LogCapture LOG(const eLogLevel level, std::source_location location)
    {
        return LogCapture{ level, std::move(location) };
    }

    void Logger::AddSink(LogSink sink)
    {
        Logger::GetInstance().m_Sinks.push_back(sink);
    }

    void Logger::Destroy()
    {
        Logger::GetInstance().DestroyImpl();
    }

    void Logger::Init()
    {
        Logger::GetInstance().InitImpl();
    }

    void Logger::PushMessage(const eLogLevel level, std::source_location&& location, std::string&& message) noexcept
    {
        auto msgPtr = std::make_shared<LogMessage>(level, std::move(location), std::move(message));

        Logger::GetInstance().QueueMessage(std::move(msgPtr));
    }

    void Logger::CallSinks(LogMessagePtr msgPtr)
    {
        for (const auto &sink : m_Sinks)
        {
            sink(msgPtr);
        }
    }

    void Logger::DestroyImpl()
    {
        m_Queue.push([this]
        {
            m_Running = false;
        });
        m_LogWorker.join();
    }

    void Logger::InitImpl()
    {
        m_Running = true;
        m_LogWorker = std::thread([this]
        {
            while (m_Running)
            {
                std::function<void()> func;
                m_Queue.wait_and_pop(func);
                func();
            }
        });
    }

    void Logger::QueueMessage(LogMessagePtr msgPtr)
    {
        m_Queue.push([this, msgPtr = std::move(msgPtr)]
        {
            CallSinks(msgPtr);
        });
    }
}