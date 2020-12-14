cmake_minimum_required(VERSION "3.16.3")

project("Distributed_Systems")

set(CMAKE_C_COMPILER mpicc)

set(SOURCES
        src/main.c
        src/showCells.c
        src/fieldFuse.c
        src/fieldSlice.c
        src/followingCellState.c
        src/followingSliceState.c
        src/followingFieldState.c)

set(HEADERS
        include/main.h
        include/showCells.h
        include/fieldFuse.h
        include/fieldSlice.h
        include/followingCellState.h
        include/followingSliceState.h
        include/followingFieldState.h)

add_executable("gameOfLife" ${SOURCES} ${HEADERS})
target_include_directories("gameOfLife" PRIVATE "include")
