cmake_minimum_required(VERSION 3.14)
project(TuProyecto)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añade el directorio de json11 al path de inclusión
include_directories(${CMAKE_SOURCE_DIR}/json11)

# Añade json11 como subdirectorio
if(EXISTS "${CMAKE_SOURCE_DIR}/json11/CMakeLists.txt")
    add_subdirectory(json11)
else()
    message(FATAL_ERROR "json11 directory not found. Please clone it into your project directory.")
endif()

# Añade tus archivos fuente
add_executable(TuProyecto
        main.cpp
        variant/variant.cpp


)

# Incluye los directorios necesarios
target_include_directories(TuProyecto PRIVATE
        ${CMAKE_SOURCE_DIR}/json11
)

# Enlaza con la biblioteca json11
target_link_libraries(TuProyecto PRIVATE json11)
