@REM Build for MINGW64 or 32 from MSYS2. 
@set OUT_DIR=Debug
@set OUT_EXE=taskmaster_win32_opengl3
@set INCLUDES=-I../../imgui -I../../
@set SOURCES=main.cpp ../../application.cpp ../../tasks.cpp ../../schedules.cpp ../../users.cpp ../../imgui/backends/imgui_impl_opengl3.cpp ../../imgui/backends/imgui_impl_win32.cpp ../../imgui/imgui.cpp ../../imgui/imgui_widgets.cpp ../../imgui/imgui_tables.cpp ../../imgui/imgui_draw.cpp ../../imgui/imgui_demo.cpp
@set LIBS=-lopengl32 -lgdi32 -ldwmapi
mkdir %OUT_DIR%
g++ -g -DUNICODE %INCLUDES% %SOURCES% -o %OUT_DIR%/%OUT_EXE%.exe --static -mwindows %LIBS% %LIBS%
