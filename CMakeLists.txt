cmake_minimum_required(VERSION 3.3)
project(raylib_template C CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MySource ${PROJECT_SOURCE_DIR}/src/*.cpp)


include_directories(${PROJECT_SOURCE_DIR}/src)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games


add_executable(${PROJECT_NAME} ${MySource})

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libs/raylib/lib/libraylib.a)
target_link_libraries(${PROJECT_NAME} winmm.lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/libs/raylib/include/)


target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(${PROJECT_NAME} PUBLIC LEVLES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/levels")