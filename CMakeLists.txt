cmake_minimum_required(VERSION 2.6) # compatibilitÃ©s de CMake
project(create_raster) # nom du projet : "create_raster"

set(CMAKE_BUILD_TYPE debug) # compilation en mode debug
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11") # options

file( # liste des fichiers Ã  compiler
  GLOB_RECURSE # recherche rÃ©cursive
  source_files # fichiers listÃ©s dans une variable source_files
  src/*.cpp # forme des fichiers Ã  rechercher
)

add_executable( # crÃ©ation de lâ€™exÃ©cutable binaire du projet
  create_raster # nom du binaire
  ${source_files} # liste des fichiers compilÃ©s pour le linking
)

target_link_libraries(${PROJECT_NAME} proj)
