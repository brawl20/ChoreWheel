@REM Build for MSVC. 
@set OUT_DIR=Debug
@set OUT_EXE=taskmaster_win32_opengl3
@set INCLUDES=/I../../imgui /I../../
@set SOURCES=main.cpp ../../application.cpp ../../tasks.cpp ../../schedules.cpp ../../users.cpp ../../imgui/backends/imgui_impl_opengl3.cpp ../../imgui/backends/imgui_impl_win32.cpp ../../imgui/imgui*.cpp
@set LIBS=/LIBPATH:../../imgui /LIBPATH:../../imgui/backends /LIBPATH:C:\Windows\System32 /LIBPATH:C:\Windows\SysWOW64 opengl32.lib gdi32.lib dwmapi.lib
mkdir %OUT_DIR%

cl /DUNICODE %INCLUDES% %SOURCES% /link /OUT:%OUT_DIR%/%OUT_EXE%.exe %LIBS% %LIBS%
del *.obj