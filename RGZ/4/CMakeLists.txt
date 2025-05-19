cmake_minimum_required(VERSION 3.10)
project(Project LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(mylib STATIC   
  mylib.c
  mylib.h
)

add_executable(KeyTable KeyTable.c)
add_executable(DeKeyTable DeKeyTable.c)

target_link_libraries(KeyTable PRIVATE mylib)
target_link_libraries(DeKeyTable PRIVATE mylib)

target_include_directories(mylib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)