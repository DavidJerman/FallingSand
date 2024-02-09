cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OLC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/olcPixelGameEngine)
set(VERSION "0.2")
add_compile_definitions(VERSION="${VERSION}")

project(FallingSand
    VERSION ${VERSION}
    DESCRIPTION "A simple falling sand game"
    LANGUAGES CXX)

set(SOURCES 
    src/main.cpp 
    src/game.cpp)

add_executable(FallingSand ${SOURCES})

target_include_directories(FallingSand PRIVATE ${INCLUDE_DIR})
target_include_directories(FallingSand PRIVATE ${OLC_DIR})
