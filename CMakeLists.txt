cmake_minimum_required(VERSION 3.27)
project(mousejoy C)

set(CMAKE_C_STANDARD 99)
set(SDL2_DIR "SDL2/cmake")
set(SDL2_NO_MWINDOWS 1)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

#add_executable(mousejoy main.c)
