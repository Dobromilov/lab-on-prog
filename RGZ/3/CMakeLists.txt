cmake_minimum_required(VERSION 3.10)
project(Project)

# Библиотека
add_library(mylib STATIC mylib.c mylib.h)

# Исполняемые файлы
add_executable(KeyTable KeyTable.c)
target_link_libraries(KeyTable mylib)

add_executable(DeKeyTable DeKeyTable.c)
target_link_libraries(DeKeyTable mylib)