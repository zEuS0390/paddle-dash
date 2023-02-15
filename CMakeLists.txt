cmake_minimum_required(VERSION 3.21)
project(pong_game_by_zEuS0390 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(SFML_NAME "SFML-2.5.1")
set(SFML_DIR "libs/${SFML_NAME}/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_BUILD_TYPE "Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(APP_SRC_FILES
	src/AI.cpp src/background.cpp 
	src/funcs.cpp src/main.cpp 
	src/menu.cpp src/players.cpp 
	src/pongball.cpp src/sound.cpp 
	src/window.cpp
)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
if (WIN32)
	add_executable(${PROJECT_NAME} WIN32 ${APP_SRC_FILES})
else()
	add_executable(${PROJECT_NAME} ${APP_SRC_FILES})
endif()

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/sfx)
if (WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/libs/${SFML_NAME}/bin/openal32.dll
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/gfx DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/sfx DESTINATION ".")
install(FILES ${PROJECT_SOURCE_DIR}/libs/${SFML_NAME}/bin/openal32.dll DESTINATION ".")

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_NAME "pong_game_by_zEuS0390")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "zEuS0390")
include(CPack)
