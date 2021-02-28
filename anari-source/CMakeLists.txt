# CMake Config (MousePaw Media Build System)
# Version: 3.2.0

# CHANGE: Name your project here
project("Anari")

# Specify the version being used.
cmake_minimum_required(VERSION 3.8)

# Import user-specified library path configuration
message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# CHANGE: Specify output binary name
set(TARGET_NAME "anari")

# SELECT: Project artifact type
set(ARTIFACT_TYPE "library")
#set(ARTIFACT_TYPE "executable")

# CHANGE: Find dynamic library dependencies.
find_library(CAIRO_LIB cairo)
find_path(CAIRO_INCLUDE_DIR cairo/cairo.h)

find_library(SDL2_LIB SDL2)
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)

# CHANGE: Include headers of dependencies.
set(INCLUDE_LIBS
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
    include/anari/colors.hpp
    include/anari/colors_test.hpp
    include/anari/config.hpp
    include/anari/demo.hpp
    include/anari/geometry.hpp
    include/anari/geometry_tests.hpp
    include/anari/hardcoded.hpp
    include/anari/layerinstance.hpp
    include/anari/layerinstance_tests.hpp
    include/anari/math.hpp
    include/anari/renderer.hpp
    include/anari/static_layer.hpp
    include/anari/static_layer.hpp
    include/anari/test_renderer.hpp
    include/anari/transformation.hpp
    include/anari/transformation_tests.hpp
    include/anari/uniform_renderer.hpp
    include/anari/window.hpp

    src/colors.cpp
    src/colors_test.cpp
    src/config.cpp
    src/demo.cpp
    src/geometry_tests.cpp
    src/layerinstance_tests.cpp
    src/math.cpp
    src/renderer.cpp
    src/static_layer.cpp
    src/test_renderer.cpp
    src/transformation_tests.cpp
    src/uniform_renderer.cpp
    src/geometry_tests.cpp
    src/static_layer.cpp
    src/window.cpp
)

# CHANGE: Link against dependencies.
set(LINK_LIBS
    ${NIMBLY_DIR}/lib/libnimbly.a
    ${GOLDILOCKS_DIR}/lib/libgoldilocks.a
    ${IOSQUEAK_DIR}/lib/libiosqueak.a
    ${CAIRO_LIB}
    ${SDL2_LIB}
)

# Imports build script. (Change if necessary to point to build.cmake)
include(${CMAKE_HOME_DIRECTORY}/../build_system/build.cmake)
