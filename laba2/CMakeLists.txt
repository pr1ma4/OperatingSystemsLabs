cmake_minimum_required(VERSION 3.24)
project(untitled14 C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

add_executable(untitled14 main.c)
target_link_libraries(untitled14 PRIVATE ${GTK_LIBRARIES})

target_include_directories(untitled14 PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(untitled14 PRIVATE ${GTK_LIBRARY_DIRS})

target_compile_options(untitled14 PRIVATE ${GTK_CFLAGS_OTHER})