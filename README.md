# AsyncLogger

Modern Asyncronous Logger using C++20 and [std::format](https://en.cppreference.com/w/cpp/utility/format/format) (falls back on [fmt::format](https://github.com/fmtlib/fmt) if not available) without using macro's!
Uses [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location) to get the location where a log was made.

## CMake variables

 - `USE_FMT` : Force AsyncLogger to use fmt formatting instead of std formatting if it's available.

## How to use

Very simple example application showing how to implement it.

main.cpp
```cpp
#include "AsyncLogger/Logger.hpp"
#include <filesystem>
#include <iostream>

// expose LOG, LOGF, eLogLevel::DEBUG, eLogLevel::INFO, etc...
using namespace al;

void COUT_LOG(LogMessagePtr msg)
{
    const auto& location = msg->Location();
    const auto file = std::filesystem::path(msg->Location().file_name()).filename().string();

    std::cout << "[" << file << ":" << location.line() << "] " << msg->Message();
}

int main()
{
    Logger::Init();
    Logger::AddSink(COUT_LOG);

    LOG(INFO) << "Test " << 1 << 2 << 3 << " some float (" << 3.5f << ")";

    Logger::Destroy();

    return 0;
}
```
Logs the following output:
```
[main.cpp:20] Test 123 some float (3.5)
```

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20 GLOBAL)

project(my_app LANGUAGES CXX VERSION 0.0.1)

add_subdirectory(AsyncLogger)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} AsyncLogger)
```

CMakeLists.txt using FetchContent
```cmake
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20 GLOBAL)

project(my_app LANGUAGES CXX VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG master
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} AsyncLogger)
```