#Define the main project name
project(SDL2_GUI)
#define CMAKE version
cmake_minimum_required(VERSION 3.10)
# Use to output all compiler commands
#set(CMAKE_VERBOSE_MAKEFILE ON)

#add extra cmake utilities to deal with SDL
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakemodules/")

#Find SDL2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#add the library we are building
add_subdirectory(SDL2_GUI)
list(APPEND EXTRA_LIBS SDL2_GUIComponents)
#add the showcase project
add_subdirectory(SDL2_GUI_Demo)



