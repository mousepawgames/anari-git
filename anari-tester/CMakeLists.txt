# CMake Config (MousePaw Media Build System)
# Version: 3.2.0

# CHANGE: Name your project here
project("Anari Tester")

# Specify the verison being used.
cmake_minimum_required(VERSION 3.8)

# Import user-specified library path configuration
message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# CHANGE: Specify output binary name
set(TARGET_NAME "anari-tester")

# SELECT: Project artifact type
#set(ARTIFACT_TYPE "library")
set(ARTIFACT_TYPE "executable")

# CHANGE: Find dynamic library dependencies.
find_library(CAIRO_LIB cairo)
find_path(CAIRO_INCLUDE_DIR cairo/cairo.h)

find_library(SDL2_LIB SDL2)
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)

# CHANGE: Include headers of dependencies.
set(INCLUDE_LIBS
    ${CMAKE_HOME_DIRECTORY}/../anari-source/include
    ${NIMBLY_DIR}/include
    ${GOLDILOCKS_DIR}/include
    ${IOSQUEAK_DIR}/include
    ${ONESTRING_DIR}/include
    ${ARCTICTERN_DIR}/include
    ${EIGEN_DIR}/include
    ${EVENTPP_DIR}/include
    ${CAIRO_INCLUDE_DIR}/cairo
    ${SDL2_INCLUDE_DIR}/SDL2
)

# CHANGE: Include files to compile.
set(FILES
    main.cpp
)

# CHANGE: Link against dependencies.
set(LINK_LIBS
    ${CMAKE_HOME_DIRECTORY}/../anari-source/lib/${CMAKE_BUILD_TYPE}/libanari.a
    ${NIMBLY_DIR}/lib/libnimbly.a
    ${GOLDILOCKS_DIR}/lib/libgoldilocks.a
    ${IOSQUEAK_DIR}/lib/libiosqueak.a
    ${CAIRO_LIB}
    ${SDL2_LIB}
)

# Imports build script. (Change if necessary to point to build.cmake)
include(${CMAKE_HOME_DIRECTORY}/../build_system/build.cmake)
