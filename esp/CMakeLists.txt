
# Min CMake version
cmake_minimum_required(VERSION 3.20)

set(SOURCE_DIR "source")
set(INCLUDE_DIR "include")

idf_component_register(
	SRCS
		${SOURCE_DIR}/BaseChunk.cpp
		${SOURCE_DIR}/TimeChunk.cpp
		${SOURCE_DIR}/UDPChunk.cpp
		${SOURCE_DIR}/WAVChunk.cpp
		${SOURCE_DIR}/WatchdogChunk.cpp
	INCLUDE_DIRS
		${INCLUDE_DIR}
)