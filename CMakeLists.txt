cmake_minimum_required(VERSION 2.8)

project(RTWG)

set(PROJECT_VERSION 0.0)

message(STATUS "~~~ ${PROJECT_NAME} - v${PROJECT_VERSION} ~~~")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
find_package(DevIL REQUIRED)
find_package(X11 REQUIRED)
find_package(AntTweakBar REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)


include_directories("${GLFW_INCLUDE_DIRS}" )
include_directories("${ANTTWEAKBAR_INCLUDE_DIR}" )
include_directories("${IL_INCLUDE_DIR}" )
include_directories("${GLM_INCLUDE_DIRS}" )

include_directories("include" )
include_directories("include/3DRender" )

include_directories("3rdParty" )


add_definitions( -std=c++14 )

add_subdirectory("3rdParty")
add_subdirectory("src")

