cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME snake)

set(SOURCES 
            main.cpp
            global.hpp
            title.hpp
            title.cpp)

add_executable(${PROJECT_NAME} ${TK_CONSOLE} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
                      SDL2
                      SDL2main
                      tk-core
                      tk-graphics
                      tk-layout
                      ${OPENGL_gl_LIBRARY})


# Configure the template file
SET(USER_FILE ${PROJECT_NAME}.vcxproj.user)
SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})
CONFIGURE_FILE(../template.vcxproj.user ${USER_FILE} @ONLY)
