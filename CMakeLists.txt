cmake_minimum_required(VERSION 3.20)
project(intro_mpi)

# Add MPI Package to Project
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_COMPILE_FLAGS}")

add_executable(intro_mpi collectiveOperation.c)
# Add libraries for code completion and compiling
#target_link_libraries(intro_mpi PUBLIC MPI::MPI_CXX)