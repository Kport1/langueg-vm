cmake_minimum_required(VERSION 3.16)
project(langueg_vm C)

set(CMAKE_C_STANDARD 99)

add_executable(langueg_vm main.c lala-load/lalafile.c lala-load/lalafile.h)