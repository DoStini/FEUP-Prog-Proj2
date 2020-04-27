# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("BoardBuilder")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Assets/WORDS.TXT
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable (BoardBuilder "main.cpp" "main.h" "fileExplorer.cpp" "fileExplorer.h" "boardIO.cpp" "boardIO.h" "color.h" "word.cpp" "word.h" 
"board.cpp" "board.h")