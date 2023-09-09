cmake_minimum_required(VERSION 3.26)

project(filler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(-Wall)

add_executable(filler 
 src/main.cpp
 src/RenderWindow.cpp
 src/Button.cpp
 src/Label.cpp
 src/GamePresenter.cpp
 src/Game.cpp
 src/RoundEntity.cpp
 src/Bubble.cpp
 src/Bludger.cpp
 src/Window.cpp
 src/InfoWindow.cpp
)

target_include_directories(filler
 PUBLIC "./include/"
)

target_link_directories(filler
 PUBLIC "./lib/"
)

target_link_libraries(filler mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)