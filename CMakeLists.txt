cmake_minimum_required(VERSION 3.21)
project(PROJECT__)

set(CMAKE_CXX_STANDARD 23)

add_executable(PROJECT__ main.cpp Creature.cpp Creature.h Hero.cpp Hero.h Enemy.cpp Enemy.h Battle.cpp Battle.h)
