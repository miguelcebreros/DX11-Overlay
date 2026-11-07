cmake_minimum_required(VERSION 3.28.3)

project(Overlay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_win32.cpp
    external/imgui/backends/imgui_impl_dx11.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)

target_link_libraries(imgui PUBLIC
    d3d11
    user32
)

add_executable(my_overlay WIN32
src/bot.cpp
src/botmanager.cpp
src/main.cpp
src/overlay.cpp
src/renderer.cpp
)

target_include_directories(my_overlay PRIVATE
    include
)

target_link_libraries(my_overlay PRIVATE imgui)