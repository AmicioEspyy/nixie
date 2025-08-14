cmake_minimum_required(VERSION 3.10)
project(nixie VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Find notcurses using pkg-config
pkg_check_modules(NOTCURSES REQUIRED notcurses)

# Print debugging information
message(STATUS "NOTCURSES_INCLUDE_DIRS: ${NOTCURSES_INCLUDE_DIRS}")
message(STATUS "NOTCURSES_LIBRARY_DIRS: ${NOTCURSES_LIBRARY_DIRS}")
message(STATUS "NOTCURSES_LIBRARIES: ${NOTCURSES_LIBRARIES}")

# Include directories
include_directories(
    ${NOTCURSES_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# Link directories
link_directories(${NOTCURSES_LIBRARY_DIRS})

# Add source files
set(SOURCES ${CMAKE_SOURCE_DIR}/main.cpp)

# Add all source files from src directory
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(APPEND SOURCES ${SRC_FILES})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (full path to avoid issues)
target_link_libraries(${PROJECT_NAME} PRIVATE ${NOTCURSES_LIBRARIES})

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${NOTCURSES_CFLAGS_OTHER})