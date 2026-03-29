cmake_minimum_required(VERSION 3.20)

project(Math3DLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####### LIBRARY SETUP #######

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "code/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "code/include/*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code/include
)

####### TEST SETUP #######

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)

    include(FetchContent)

    # Fix for Visual Studio runtime
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )

    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_subdirectory(tests/UnitTests)

endif()