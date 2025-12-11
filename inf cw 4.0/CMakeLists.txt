cmake_minimum_required(VERSION 3.10)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Arkanoid
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/GameState.cpp
    src/GameState.h
    src/Menu.cpp
    src/Menu.h
    src/Paletka.cpp
    src/Paletka.h
    src/Pilka.cpp
    src/Pilka.h
    src/Stone.cpp
    src/Stone.h
)

target_link_libraries(Arkanoid PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
