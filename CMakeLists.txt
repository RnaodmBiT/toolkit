cmake_minimum_required(VERSION 3.2)

project (toolkit)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

add_subdirectory(core)
add_subdirectory(layout)