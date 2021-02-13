cmake_minimum_required(VERSION 3.10)

project(CSCSnake)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

set(SOURCE_PATH src/)

set(SOURCES ${SOURCE_PATH}main.cpp
	${SOURCE_PATH}Entity.cpp
	${SOURCE_PATH}GameManager.cpp
	${SOURCE_PATH}SnakeHead.cpp
	${SOURCE_PATH}SnakePart.cpp
	${SOURCE_PATH}SnakeController.cpp
	${SOURCE_PATH}Renderer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2)
