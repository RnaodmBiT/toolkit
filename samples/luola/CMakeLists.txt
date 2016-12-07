cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME luola)

set(SOURCES 
            main.cpp 
            global.hpp messages.hpp
            player_info.hpp player_info.cpp
            title.hpp title.cpp
            game_server.hpp game_server.cpp
            game.hpp game.cpp
            ship.hpp ship.cpp
            controller.hpp player.cpp
            button.hpp
)



add_executable(${PROJECT_NAME} ${TK_CONSOLE} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
                      SDL2 SDL2main
                      tk-core tk-graphics tk-net
                      ${OPENGL_gl_LIBRARY})


# Configure the template file
SET(USER_FILE ${PROJECT_NAME}.vcxproj.user)
SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})
CONFIGURE_FILE(../template.vcxproj.user ${USER_FILE} @ONLY)
