#Project name: network adapter info
cmake_minimum_required(VERSION 3.5)
project(netadainfo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
message(STATUS "CMake version: ${CMAKE_VERSION}")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(WARNING "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
    message(STATUS "Please use a different C++ compiler.")
    message(FATAL_ERROR "Only support C++11 compiler! Please download C++11 Compiler")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")

set(GIT_COMMIT_HASH "")
set(GIT_BRANCH_NAME "")
find_package(Git QUIET)
if(GIT_FOUND)
execute_process(
    #Format %ci time yyyy-mm-dd hh:mm:ss %H commitID
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%ci%H
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
    OUTPUT_VARIABLE GIT_BRANCH_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()
set(APP_VERSION "VersionInfo: ${GIT_BRANCH_NAME}:${GIT_COMMIT_HASH}")
message(STATUS  ${APP_VERSION})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/ver.h.ini
  ${CMAKE_BINARY_DIR}/ver.h
  @ONLY
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PROJECT_SOURCES)

#add_library(netadainfo ${PROJECT_SOURCES})

add_executable(netadainfo ${PROJECT_SOURCES})

target_link_libraries(netadainfo)
