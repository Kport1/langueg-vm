cmake_minimum_required(VERSION 3.16)
project(langueg_vm C)

set(CMAKE_C_STANDARD 99)

add_executable(langueg_vm main.c load/lalafile.c load/lalafile.h util/byte-iterator.h error/error.c error/error.h vm/langueg-vm.c vm/langueg-vm.h vm/instructions.h stack/stack.h)