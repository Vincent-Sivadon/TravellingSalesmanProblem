cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(TSP)

# Liste des fichiers sources
file(GLOB SRCS "${CMAKE_SOURCE_DIR}/src/*")

# Liste des headers
file(GLOB HDRS "${CMAKE_SOURCE_DIR}/include/*")

add_library(TSP SHARED ${SRCS} ${HDRS})
target_include_directories(TSP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(prog prog.c)
target_link_libraries(prog TSP)
target_compile_options(prog PUBLIC -g)

# Tests
add_subdirectory(test)

add_custom_target(test COMMAND echo "---------------------"
                       COMMAND regret
                       COMMAND bound
                       COMMAND mask
                       COMMAND echo "---------------------"
                       )