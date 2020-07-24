cmake_minimum_required(VERSION 3.10)
project(stereogram)

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_basic_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})