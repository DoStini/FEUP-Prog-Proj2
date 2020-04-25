# CMakeList.txt : CMake project for BoardBuilder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/WORDS.TXT
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable (BoardBuilder "main.cpp" "main.h" "fileExplorer.cpp" "fileExplorer.h" "boardIO.cpp" "boardIO.h" "color.h" "word.cpp" "word.h" 
"board.cpp" "board.h")

# TODO: Add tests and install targets if needed.
