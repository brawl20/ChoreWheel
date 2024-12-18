cmake_minimum_required(VERSION 3.6)

project(TaskMaster)

set(CMAKE_CXX_STANDARD 19)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(${CMAKE_PROJECT_NAME} SHARED 
  ${CMAKE_CURRENT_SOURCE_DIR}/builds/win32_opengl3/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_win32.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

#add_library(${CMAKE_PROJECT_NAME} SHARED
#  ${CMAKE_CURRENT_SOURCE_DIR}/builds/android_opengl3/main.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_android.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
#  ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
#)

if(${CMAKE_VS_PLATFORM_NAME})
endif()

#set(CMAKE_SHARED_LINKER_FLAGS
#  "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
#)

#target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
#  IMGUI_IMPL_OPENGL_ES3
#)

#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
#  ${CMAKE_CURRENT_SOURCE_DIR}/../..
#  ${CMAKE_CURRENT_SOURCE_DIR}/../../backends
#  ${ANDROID_NDK}/sources/android/native_app_glue
#)

#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
#  android
#  EGL
#  GLESv3
#  log
#)
