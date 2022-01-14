cmake_minimum_required(VERSION 3.20)
project(mazeGameProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(mazeGameProject main.cpp Gate.cpp Maze.cpp Player.cpp Post.cpp Robot.cpp ChooseMaze.cpp Game.cpp)
