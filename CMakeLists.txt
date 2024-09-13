cmake_minimum_required(VERSION 3.10)

# Set Clang as the default compiler
# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")

project(test)

# if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     message(FATAL_ERROR "This project must be built with Clang (or, on Windows, clang-cl)")
# endif()

## ============================================================================
##  Global CMake Variables.
## ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## ============================================================================
##  Global compiler options.
## ============================================================================
## Turn on diagnostics colours.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
else()
    add_compile_options(-fdiagnostics-color=auto)
endif()


# Find the SFML package (make sure SFML is installed in your system or provide the path)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

file( GLOB SRC_FILES "src/*.cpp")
# Add the source files
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

# Link the SFML libraries to your project
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
