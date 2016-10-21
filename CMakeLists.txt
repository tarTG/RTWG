cmake_minimum_required(VERSION 2.8)

project(RTWG)

set(PROJECT_VERSION 0.0)

message(STATUS "~~~ ${PROJECT_NAME} - v${PROJECT_VERSION} ~~~")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")



include_directories("include" )
include_directories("3rdParty" )


add_definitions( -std=c++14 )

add_subdirectory("3rdParty")
add_subdirectory("src")

