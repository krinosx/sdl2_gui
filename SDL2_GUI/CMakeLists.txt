cmake_minimum_required(VERSION 3.10)

project(LIB_SDL2_GUI)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

#Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(LIB_SDL2_GUI GUIButton.cpp 
                    GUIComponent.cpp 
                    GUILabel.cpp 
                    GUIManager.cpp 
                    GUIPanel.cpp
                    GUIScrollbar.cpp
                    GUIScrollPanel.cpp
                    GUISpinner.cpp 
                    GUITextArea.cpp 
                    GUITextField.cpp)  


target_link_libraries(LIB_SDL2_GUI ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY} )


