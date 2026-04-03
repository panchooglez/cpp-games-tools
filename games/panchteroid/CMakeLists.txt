cmake_minimum_required(VERSION 3.14)
project(panchteroid)

# Exigimos C++20 para poder usar concepts y rangos
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- LA MAGIA: Descargar Raylib desde GitHub automáticamente ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0  # Usamos la última versión estable
)
FetchContent_MakeAvailable(raylib)
# ---------------------------------------------------------------

# Le decimos a CMake dónde encontrar tus archivos .hpp
include_directories(include)

# Creamos tu programa (añade aquí todos los .cpp que vayas creando en src/)
add_executable(Juego 
    main.cpp
    src/physics.cpp
)

# Enlazamos Raylib a tu juego
target_link_libraries(Juego PRIVATE raylib)