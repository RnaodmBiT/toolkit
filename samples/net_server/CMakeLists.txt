cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME net_server)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} tk-core tk-net)


# Configure the template file
SET(USER_FILE ${PROJECT_NAME}.vcxproj.user)
SET(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})
CONFIGURE_FILE(../template.vcxproj.user ${USER_FILE} @ONLY)
