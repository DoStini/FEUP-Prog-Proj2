cmake_minimum_required(VERSION 3.15)
project(ScrabbleJunior)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

configure_file(board.txt
               ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(board2.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(ScrabbleJunior main.cpp Player.h Word.h Game.h Board.cpp Board.h Word.cpp Game.cpp Color.h IO.cpp IO.h Player.cpp Menu.h Menu.cpp)