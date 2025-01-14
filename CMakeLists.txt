cmake_minimum_required(VERSION 3.28)
project(PathfindingVisualiser LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add all source files
set(SOURCES
        src/main.cpp
        src/application.cpp
        src/camera.cpp
        src/grid.cpp
        src/gridRenderer.cpp
        src/menu.cpp
        imgui/imgui.cpp
        imgui/imgui-SFML.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
)

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE inc imgui)
target_link_libraries(main PRIVATE SFML::Graphics)
