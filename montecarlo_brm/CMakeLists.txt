cmake_minimum_required(VERSION 3.0)

project(montecarlo_brm)

find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
add_compile_options(-Wall -Wpedantic)


set(SRCS
    noeud.cc
    relation.cc
    arbre.cc
    montecarlo.cc
    )
    
set(HEADERS
    noeud.hh
    relation.hh
    arbre.hh
    utilitaire.hh
    montecarlo.hh
    )

add_library(montecarlo_brm ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
