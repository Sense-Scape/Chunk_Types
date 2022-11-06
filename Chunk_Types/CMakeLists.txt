# CMake instructions to make the static lib

# Min CMake version
cmake_minimum_required(VERSION 3.20)

# What to add to library
add_library(SC_Chunk_Types 
			STATIC
			"ChunkTypes.h"
			"SessionModeTypes.h"
			"BaseChunk.h"
			"BaseChunk.cpp" 
			"TimeChunk.h"
			"TimeChunk.cpp"
			"UDPChunk.h"
			"UDPChunk.cpp"
			"WAVChunk.h"
			"WAVChunk.cpp"
			)
