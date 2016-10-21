cmake_minimum_required(VERSION 2.9)

project(RTWG)

set(PROJECT_VERSION 0.0)

message(STATUS "~~~ ${PROJECT_NAME} - v${PROJECT_VERSION} ~~~")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(LibNoise REQUIRED)


include_directories("include" )
include_directories("3rdParty" )

include_directories("${LIBNOISE_INCLUDE_DIR}" )

add_definitions( -std=c++14 )

add_subdirectory("3rdParty")
add_subdirectory("src")

