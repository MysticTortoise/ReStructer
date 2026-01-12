cmake_minimum_required(VERSION 3.20)
project(ReStructer)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources source/*.c*)
message(${sources})
add_library(ReStructer ${sources})
target_include_directories(ReStructer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")


add_executable(ReStructer_Test test/main.cpp)
target_link_libraries(ReStructer_Test ReStructer)