cmake_minimum_required(VERSION "3.16.3")

project("Distributed_Systems")

set(SOURCES
        src/main.c
        src/showCells.c
        src/followingCellState.c
        src/followingFieldState.c)

set(HEADERS
        include/main.h
        include/showCells.h
        include/followingCellState.h
        include/followingFieldState.h)

add_executable("gameOfLife" ${SOURCES} ${HEADERS})
target_include_directories("gameOfLife" PRIVATE "include")
