﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("BoardBuilder")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (BoardBuilder "main.cpp" "main.h" "fileExplorer.cpp" "fileExplorer.h" "boardIO.cpp" "boardIO.h" "color.h" "word.cpp" "word.h" 
"board.cpp" "board.h" "menu.h" "menu.cpp")

