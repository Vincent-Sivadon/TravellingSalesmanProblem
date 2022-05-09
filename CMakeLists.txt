cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(TSP)

# Liste des fichiers sources
file(GLOB SRCS "${CMAKE_SOURCE_DIR}/src/*")

# Liste des headers
file(GLOB HDRS "${CMAKE_SOURCE_DIR}/include/*")

add_library(TSP SHARED ${SRCS} ${HDRS})
target_include_directories(TSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_options(TSP PUBLIC -g)

add_executable(prog prog.c)
target_link_libraries(prog PUBLIC TSP)
target_compile_options(prog PUBLIC -g)


enable_testing()
add_subdirectory(test)