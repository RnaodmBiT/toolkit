cmake_minimum_required(VERSION 3.2)

add_executable(hello_world ${TK_CONSOLE} main.cpp)
target_link_libraries(hello_world SDL2 SDL2main tk-graphics ${OPENGL_gl_LIBRARY})


# Configure the template file
SET(USER_FILE hello_world.vcxproj.user)
SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})
CONFIGURE_FILE(../template.vcxproj.user ${USER_FILE} @ONLY)
