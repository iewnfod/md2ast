cmake_minimum_required(VERSION 3.17)
project(md2ast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

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

add_library(md2ast SHARED ${SOURCES} ${HEADERS})

target_include_directories(md2ast PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(md4c PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/md4c/src
)

target_link_libraries(md2ast PRIVATE md4c)

add_executable(md2ast-test ${SOURCES} ${HEADERS})
