cmake_minimum_required(VERSION 3.16)
project(project C)

set(CMAKE_C_STANDARD 90)

add_executable(A A.c ../util/util.c)
add_executable(P P.c ../util/util.c)
add_executable(C C.c ../util/util.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(A Threads::Threads)
target_link_libraries(P Threads::Threads)
target_link_libraries(C Threads::Threads)