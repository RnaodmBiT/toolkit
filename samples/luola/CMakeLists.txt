cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME luola)

file(GLOB_RECURSE SOURCES *.cpp *.hpp)
foreach(FILE ${SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" PATH)

    # skip src or include and changes /'s to \\'s
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\\\" GROUP "${GROUP}")
    string(REGEX REPLACE "^\\\\" "" GROUP "${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_executable(${PROJECT_NAME} ${TK_CONSOLE} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
                      SDL2 SDL2main
                      tk-core tk-graphics tk-net
                      ${OPENGL_gl_LIBRARY})


# Configure the template file
SET(USER_FILE ${PROJECT_NAME}.vcxproj.user)
SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})
CONFIGURE_FILE(../template.vcxproj.user ${USER_FILE} @ONLY)
