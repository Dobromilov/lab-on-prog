cmake_minimum_required(VERSION 3.10)
project(Project)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(mylib SHARED 
  mylib.c
  mylib.h
)

set_target_properties(mylib PROPERTIES
  VERSION 1.0.0
  SOVERSION 1
)

add_executable(KeyTable KeyTable.c)
add_executable(DeKeyTable DeKeyTable.c)

target_link_libraries(KeyTable PRIVATE mylib)
target_link_libraries(DeKeyTable PRIVATE mylib)

# пути к заголовочным файлам (чтоб компилятор видел где искачть заголовки)
target_include_directories(mylib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)