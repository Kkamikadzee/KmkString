cmake_minimum_required(VERSION 3.0.0)
project(KmkString)

file(GLOB CPP_SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)