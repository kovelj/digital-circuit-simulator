add_executable(CircuitSimulator "../app/main.cpp")

target_sources(CircuitSimulator
        PRIVATE
            Simulator.cpp
            Ispis.cpp
            Citanje.cpp
            Element.cpp
)

target_include_directories(CircuitSimulator
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
)

# 4. Inject the absolute test path directly into the compiler
target_compile_definitions(CircuitSimulator
        PRIVATE
            TEST_DIR="${PROJECT_SOURCE_DIR}/test"
)