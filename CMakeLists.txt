cmake_minimum_required(VERSION 3.2)

project(toolkit)

set(CMAKE_CXX_STANDARD 11)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

# Add the include directories
include_directories(
    core/include
    layout/include
    graphics/include
    net/include
)

# Add toolkit libraries
add_subdirectory(core)
add_subdirectory(layout)
add_subdirectory(graphics)
add_subdirectory(net)


# Add sample projects
add_subdirectory(samples)

# Add thirdparty libraries
add_subdirectory(thirdparty/SDL2-2.0.4)
