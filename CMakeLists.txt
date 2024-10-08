# Set minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name and version
project(PaddleDash VERSION 1.1.1)

option(PADDLEDASH_GENERATE_INSTALLER "Generate an installer" FALSE)
option(BUILD_SHARED_LIBS "Build Shared Libs" OFF)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Define source files
set(APP_ICON_RC "${CMAKE_SOURCE_DIR}/rc/icon.rc")
set(APP_SRC_FILES
	src/AI.cpp src/background.cpp
	src/funcs.cpp src/main.cpp
	src/menu.cpp src/players.cpp
	src/pongball.cpp src/sound.cpp
	src/window.cpp
)

set(FETCHCONTENT_QUIET FALSE)

# Include SFML using FetchContent
include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SFML)

# Configure build based on platform
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	# Windows specific settings
	add_executable(${PROJECT_NAME} WIN32 ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system
		-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
else()
	# Other platforms (assuming Unix-like)
	add_executable(${PROJECT_NAME} ${APP_SRC_FILES})
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()

configure_file(
        "${CMAKE_SOURCE_DIR}/include/version.hpp.in"
        "${CMAKE_SOURCE_DIR}/include/version.hpp"
)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Copy directories and files before build
add_custom_command(
	TARGET ${PROJECT_NAME}
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND}
	-E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)

add_custom_command(
	TARGET ${PROJECT_NAME}
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/sfx)

# Additional copy for Windows (specifically openal32.dll)
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	add_custom_command(
		TARGET ${PROJECT_NAME}
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
		VERBATIM)
endif()

if (PADDLEDASH_GENERATE_INSTALLER)
	install(TARGETS ${PROJECT_NAME} DESTINATION ".")
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/gfx DESTINATION ".")
	install(DIRECTORY ${PROJECT_SOURCE_DIR}/sfx DESTINATION ".")
	install(FILES
		${PROJECT_SOURCE_DIR}/LICENSE
		$<$<PLATFORM_ID:Windows>:${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll>
		DESTINATION ".")
	set(CPACK_GENERATOR "NSIS")
	set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
	set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
	set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
	set(CPACK_VENDOR_NAME "zEuS0390")
	if (CPACK_GENERATOR MATCHES "NSIS")
		list(APPEND CPACK_NSIS_CREATE_ICONS_EXTRA
			"CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'"
			"CreateShortCut '$DESKTOP\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'")
		list(APPEND CPACK_NSIS_DELETE_ICONS_EXTRA
			"Delete '$SMPROGRAMS\\\\$START_MENU\\\\${PROJECT_NAME}.lnk'"
			"Delete '$DESKTOP\\\\${PROJECT_NAME}.lnk'")
		string(REPLACE ";" "\n" CPACK_NSIS_CREATE_ICONS_EXTRA "${CPACK_NSIS_CREATE_ICONS_EXTRA}")
		string(REPLACE ";" "\n" CPACK_NSIS_DELETE_ICONS_EXTRA "${CPACK_NSIS_DELETE_ICONS_EXTRA}")
	endif()
	include(CPack)
endif()

