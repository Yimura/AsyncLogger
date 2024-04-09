#pragma once
#if !defined(USE_FMT) && CXX_FORMAT_SUPPORT
    #include <format>
    #define FORMAT std::format
    #define VFORMAT std::vformat
    #define MAKE_FORMAT_ARGS std::make_format_args
#else
    #include <fmt/core.h>
    #define FORMAT fmt::format
    #define VFORMAT fmt::vformat
    #define MAKE_FORMAT_ARGS fmt::make_format_args
#endif
#include <functional>
#include "concurrency/shared_queue.hpp"
#include "LogCapture.hpp"
#include "LogIntermediate.hpp"
#include "LogLevel.hpp"
#include "LogMessage.hpp"

namespace al
{
    using LogMessagePtr = std::shared_ptr<LogMessage>;
    using LogSink = std::function<void(LogMessagePtr)>;

    class Logger
    {
    public:
        Logger() = default;
        virtual ~Logger() = default;

        static void AddSink(LogSink sink);
        static void Destroy();
        static void Init();
        /**
         * @brief Attempts to flush the log queue immediately until it's completely empty.
         */
        static void FlushQueue();

    protected:
        static void PushMessage(const eLogLevel level, std::chrono::system_clock::time_point&& timestamp, std::source_location&& location, std::string&& message) noexcept;

    private:
        void CallSinks(LogMessagePtr msgPtr);
        void DestroyImpl();
        void InitImpl();
        /**
         * @brief Attempts to flush the entire log queue before returning
         */
        void FlushQueueImpl();
        void QueueMessage(LogMessagePtr msgPtr);

        static Logger& GetInstance()
        {
            static Logger i{};
            return i;
        }

    private:
        friend LogCapture::~LogCapture();

        shared_queue<std::function<void()>> m_Queue;
        std::vector<LogSink> m_Sinks;
        bool m_Running = false;
        std::thread m_LogWorker;

    };

    extern LogCapture LOG(const eLogLevel level, std::source_location location = std::source_location::current());

    template<typename ...Args>
    inline void LOGF(const eLogLevel level, LogIntermediate formatString, Args&&... formatArgs)
    {
        auto capture = LogCapture(level, std::move(formatString.Location()));
        capture << VFORMAT(formatString.FormatString(), MAKE_FORMAT_ARGS(std::forward<Args>(formatArgs)...));
    }
}
