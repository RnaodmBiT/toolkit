cmake_minimum_required(VERSION 3.2)

project (toolkit)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

# Add toolkit libraries
add_subdirectory(core)
add_subdirectory(layout)

# Add sample projects
add_subdirectory(samples)

# Add thirdparty libraries
add_subdirectory(thirdparty/SDL2-2.0.4)
