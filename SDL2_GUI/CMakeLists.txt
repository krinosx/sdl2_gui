#Define the name of current module/lib
project(SDL2_GUIComponents)
cmake_minimum_required(VERSION 3.10)


#Library and sourcefiles
add_library(SDL2_GUIComponents GUIButton.cpp 
                    GUIComponent.cpp 
                    GUILabel.cpp 
                    GUIManager.cpp 
                    GUIPanel.cpp
                    GUIScrollbar.cpp
                    GUIScrollPanel.cpp
                    GUISpinner.cpp 
                    GUITextArea.cpp 
                    GUITextField.cpp)  


#target_link_libraries(LIB_SDL2_GUI ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY} )
target_link_libraries(SDL2_GUIComponents ${SDL2_LIBRARIES})
target_link_libraries(SDL2_GUIComponents ${SDL2_TTF_LIBRARY})
target_link_libraries(SDL2_GUIComponents ${SDL2_IMAGE_LIBRARIES})