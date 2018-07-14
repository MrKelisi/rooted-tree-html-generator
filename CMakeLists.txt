cmake_minimum_required(VERSION 3.0)
project(rooted-tree-html-generator)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        TExprArb.h
        Source.cpp)

add_executable(rooted-tree-html-generator ${SOURCE_FILES})