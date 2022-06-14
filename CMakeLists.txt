cmake_minimum_required(VERSION 3.22)
project(libjson C)

set(CMAKE_C_STANDARD 23)

add_library(json SHARED src/library.c src/string.c src/number.c src/boolean.c src/null.c src/array.c src/object.c src/string_utils.c)

target_include_directories(json PUBLIC include)
target_include_directories(json PRIVATE src)

add_executable(tests tests/main.c)
target_link_libraries(tests json)