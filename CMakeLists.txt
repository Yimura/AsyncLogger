cmake_minimum_required(VERSION 3.20)

option(USE_FMT "Use fmt::format instead of std::format" 0)

project(AsyncLogger LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "A lightweight C++20 asyncronous logger.")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(PUBLIC_HEADER_DIR "${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.hpp"
)
file(GLOB_RECURSE PUBLIC_HEADER_FILES
    "${PUBLIC_HEADER_DIR}/**.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${PUBLIC_HEADER_FILES})

# check std::format support
include(CheckIncludeFileCXX)
check_include_file_cxx("format" CXX_FORMAT_SUPPORT)

if(CXX_FORMAT_SUPPORT AND NOT USE_FMT)
    message(STATUS "Using std::format for formatting, you can set USE_FMT to force fmt::format instead.")
else()
    message(STATUS "Using fmt::format for formatting.")
    include(FetchContent)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(fmt)

    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FMT=1)
    target_link_libraries(${PROJECT_NAME} fmt)
endif()

unset(USE_FMT CACHE)
unset(CXX_FORMAT_SUPPORT CACHE)

# does the -lpthread linking for us on Linux
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PRIVATE "${PUBLIC_HEADER_DIR}/AsyncLogger/")
target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}")
target_precompile_headers(${PROJECT_NAME} PRIVATE "${SRC_DIR}/common.hpp")

# public stuff
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_FILES}")
target_include_directories(${PROJECT_NAME} PUBLIC "${PUBLIC_HEADER_DIR}")
