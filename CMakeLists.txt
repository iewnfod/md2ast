cmake_minimum_required(VERSION 3.17)
project(md2ast)

set(CMAKE_CXX_STANDARD 17)

add_library(
    md4c STATIC
    lib/md4c/src/md4c.c lib/md4c/src/md4c-html.c lib/md4c/src/entity.c
)

include_directories(src)
include_directories(lib/md4c/src)

file(
    GLOB SOURCES
    "*.cpp" "src/*.cpp" "lib/md4c/src/*.c"
)
file(
    GLOB HEADERS
    "*.h" "src/*.h" "lib/md4c/src/*.h"
)

add_executable(md2ast ${SOURCES} ${HEADERS})
