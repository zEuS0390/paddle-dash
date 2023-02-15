cmake_minimum_required(VERSION 3.21)
project(SFML_PONG_GAME)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
add_executable(SFML_PONG_GAME 
	src/AI.cpp src/background.cpp 
	src/funcs.cpp src/main.cpp 
	src/menu.cpp src/players.cpp 
	src/pongball.cpp src/sound.cpp 
	src/window.cpp
)
target_link_libraries(SFML_PONG_GAME sfml-audio sfml-graphics sfml-window sfml-system)
target_include_directories(SFML_PONG_GAME PRIVATE include)

add_custom_command(TARGET SFML_PONG_GAME POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:SFML_PONG_GAME>/gfx)
add_custom_command(TARGET SFML_PONG_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:SFML_PONG_GAME>/sfx)
