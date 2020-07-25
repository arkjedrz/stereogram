cmake_minimum_required(VERSION 3.10)
project(stereogram)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/file_helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sirds_generator.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})