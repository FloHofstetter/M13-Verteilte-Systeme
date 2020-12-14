cmake_minimum_required(VERSION "3.16.3")

project("Distributed_Systems")

set(CMAKE_C_COMPILER mpicc)

set(SOURCES
        src/main.c
        src/showCells.c
        src/fieldFuse.c
        src/fieldSlice.c
        src/showNumbers.c
        src/followingCellState.c
        src/followingSliceState.c
        )

set(HEADERS
        include/showCells.h
        include/fieldFuse.h
        include/fieldSlice.h
        include/showNumbers.h
        include/followingCellState.h
        include/followingSliceState.h
        )

add_executable("gameOfLife" ${SOURCES} ${HEADERS})
target_include_directories("gameOfLife" PRIVATE "include")
