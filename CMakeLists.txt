cmake_minimum_required(VERSION 3.23)

project(CircuitSimulator LANGUAGES CXX)

add_executable(CircuitSimulator)

target_sources(CircuitSimulator
              PRIVATE
              app/main.cpp
              src/Simulator.cpp
              src/Ispis.cpp
              src/Citanje.cpp
              src/Element.cpp)

target_include_directories(CircuitSimulator
        PRIVATE
        include
)
