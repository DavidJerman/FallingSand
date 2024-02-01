cmake_minimum_required(VERSION 3.15)

project(FallingSand
    VERSION 0.1
    DESCRIPTION "A simple falling sand game"
    LANGUAGES CXX)

include_directories(
    include
    olcPixelGameEngine
)

add_executable(FallingSand
    src/main.cpp
    src/game.cpp
)
