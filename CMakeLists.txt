cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MyFTP VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FILE(GLOB ALL_SOURCES "*.cpp")
FILE(GLOB ALL_INCLUDES "*.h")
SET (ALL_SRCS ${ALL_SOURCES} ${ALL_INCLUDES})

# add the executable
add_executable(ftpserver ${ALL_SRCS})