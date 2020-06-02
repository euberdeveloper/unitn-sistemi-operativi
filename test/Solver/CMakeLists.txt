cmake_minimum_required(VERSION 3.16)
project(project C)

set(CMAKE_C_STANDARD 90)

add_executable(analyzer A.c ../util/util.c)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(analyzer Threads::Threads)