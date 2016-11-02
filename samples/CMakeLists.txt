cmake_minimum_required(VERSION 3.2)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SDL2-2.0.4/include)

option(TK_DISABLE_CONSOLE "Disable the Win32 console for the samples" OFF)

if (TK_DISABLE_CONSOLE)
    set(TK_CONSOLE WIN32)
endif()

find_package(OpenGL)

# add all of the sample directories
add_subdirectory(hello_world)
add_subdirectory(pong)
