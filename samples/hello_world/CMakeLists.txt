cmake_minimum_required(VERSION 3.2)

add_executable(hello_world ${TK_CONSOLE} main.cpp)
target_link_libraries(hello_world SDL2 SDL2main tk-graphics ${OPENGL_gl_LIBRARY})

