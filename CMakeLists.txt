cmake_minimum_required(VERSION 4.0)
project(adonis C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(adonis
        adonis.c
        drawing.c
        drawing.h
)
