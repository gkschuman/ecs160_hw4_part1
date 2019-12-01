cmake_minimum_required(VERSION 3.13)
project(HW4_Part1 C)

set(CMAKE_C_STANDARD 11)

add_executable(HW4_Part1 maxTweeter.c)
target_compile_options(HW4_Part1 PRIVATE -Wall -Wextra -Werror)