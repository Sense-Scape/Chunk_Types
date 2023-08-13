cmake_minimum_required(VERSION 3.10)
project(ChunkTypesProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Main executable
add_library(ChunkTypesLib
    source/BaseChunk.cpp
    source/JSONChunk.cpp
    source/TimeChunk.cpp
    source/UDPChunk.cpp
    source/WAVChunk.cpp
    source/WatchdogChunk.cpp
)

# Test executable
add_executable(ChunkTypesTests
    source_tests/ChunkTypesTest.cpp 
)

# Include directories for main code and tests
target_include_directories(ChunkTypesLib
    PRIVATE include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components/Nlohmann_JSON/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components/Nlohmann_JSON/include/nlohmann
)

target_include_directories(ChunkTypesTests
    PRIVATE include
    PRIVATE include_tests
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components/doctest/doctest
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components/Nlohmann_JSON/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components/Nlohmann_JSON/include/nlohmann
)

# Add components (even if no CMakeLists.txt)
add_subdirectory(components/doctest)

# Link with required libraries for the main executable
target_link_libraries(ChunkTypesLib PRIVATE doctest::doctest)

# Link with required libraries for the test executable
target_link_libraries(ChunkTypesTests PRIVATE ChunkTypesLib doctest::doctest)

# Enable testing
enable_testing()

# Add tests to CTest
add_test(NAME ChunkTypesTests COMMAND ChunkTypesTests)
