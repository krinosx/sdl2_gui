project(SDL2_GUI_DEMO)

cmake_minimum_required(VERSION 3.10)

# Define output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(SDL2_GUI_DEMO SDL2_GUI_Demo.cpp)

target_link_libraries(SDL2_GUI_DEMO ${SDL2_LIBRARIES})
target_link_libraries(SDL2_GUI_DEMO ${SDL2_TTF_LIBRARY})
target_link_libraries(SDL2_GUI_DEMO ${SDL2_IMAGE_LIBRARIES})
#Link agains our library
target_link_libraries(SDL2_GUI_DEMO SDL2_GUIComponents)


target_include_directories(SDL2_GUI_DEMO PUBLIC "${CMAKE_BINARY_DIR}/SDL2_GUI")


