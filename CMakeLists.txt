cmake_minimum_required(VERSION 3.5)

project(zuma-deluxe LANGUAGES C CXX ASM)

file(GLOB SOURCES
	SexyAppFramework/*.cpp
	SexyAppFramework/graphics/*.cpp
	SexyAppFramework/imagelib/*.cpp
	SexyAppFramework/misc/*.cpp
	SexyAppFramework/paklib/*.cpp
	SexyAppFramework/sound/*.cpp
	SexyAppFramework/widget/*.cpp
	SexyAppFramework/fcaseopen/*.c
	CircleShoot/*.cpp
)

set(DOWNSCALE_COUNT 1)

set(VORBIS_LIBS vorbisfile vorbis)

option(CONSOLE "Show console on Windows" ON)

find_package(ZLIB REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

set(SDL_MIXER_X_STATIC ON CACHE BOOL "Build static library of SDL Mixer X" FORCE)
set(SDL_MIXER_X_SHARED OFF CACHE BOOL "Build shared library of SDL Mixer X" FORCE)
set(USE_MIDI OFF CACHE BOOL "SDL Mixer X midi" FORCE)
set(USE_MODPLUG OFF CACHE BOOL "SDL Mixer X modplug" FORCE)
set(USE_XMP OFF CACHE BOOL "SDL Mixer X xmp" FORCE)
set(USE_OPUS OFF CACHE BOOL "SDL Mixer X opus" FORCE)
set(USE_DRFLAC OFF CACHE BOOL "SDL Mixer X flac" FORCE)
set(USE_PXTONE OFF CACHE BOOL "SDL Mixer X pxtone" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/SDL-Mixer-X)

add_executable(zuma-deluxe ${SOURCES})
target_include_directories(zuma-deluxe PRIVATE
	${PROJECT_SOURCE_DIR}/SexyAppFramework
	${PROJECT_SOURCE_DIR}/SDL-Mixer-X/include
	${SDL2_INCLUDE_DIRS}
	${PLAT_INCLUDES}
)
target_compile_definitions(zuma-deluxe PRIVATE _DEBUG)
target_compile_definitions(zuma-deluxe PRIVATE IMG_DOWNSCALE=${DOWNSCALE_COUNT})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_BINARY_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR}/SexyAppFramework)

target_link_libraries(zuma-deluxe jpeg png z m SDL2_mixer_ext_Static openmpt mpg123 GL ${VORBIS_LIBS} ogg ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})




