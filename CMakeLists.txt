cmake_minimum_required(VERSION 3.10)

project(CUtils)

#option(__DEBUG__ "" ON)

set(CMAKE_C_FLAGS "-no-pie -g -O2")

add_library(cutils SHARED src/cstring.c src/cvector.c)
target_include_directories(cutils
PUBLIC
    src/include
)

install(TARGETS cutils
    LIBRARY DESTINATION lib
)

install(DIRECTORY src/include/
    DESTINATION include
)