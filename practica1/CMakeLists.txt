cmake_minimum_required(VERSION 3.10)
project(InferenciaCondicional)

# Estándar C++11 para soporte de strings y matemáticas [cite: 80]
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluimos el directorio src para que encuentre los archivos .h
include_directories(src)

# Definimos los archivos fuente especificando su ruta en src/
set(SOURCES 
    src/codigo.cc 
    src/data.cc 
    src/data.h
)

# Crear el ejecutable
add_executable(programa_inferencia ${SOURCES})