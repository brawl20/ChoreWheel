cmake_minimum_required(VERSION 3.6)

project(TaskMaster)

set(CMAKE_CXX_STANDARD 19)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

add_library()