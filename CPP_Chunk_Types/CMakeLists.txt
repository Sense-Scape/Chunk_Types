# CMake instructions to make the static lib

# Min CMake version
cmake_minimum_required(VERSION 3.24)

# Project name and langues (C, C++, Assembly)
project(SC_Chunk_Types C CXX ASM)

# What to add to library
add_library(Cpp_Chunk_Types 
			STATIC
			ChunkTypes.h
			ChunkTypes.cpp
			SessionModeTypes.h
			BaseChunk.h
			BaseChunk.cpp 
			TimeChunk.h
			TimeChunk.cpp
			UDPChunk.h
			UDPChunk.cpp
			WAVChunk.h
			WAVChunkcpp
			)

# Adding sources to library
target_sources(Cpp_Chunk_Types
				PUBLIC 
				ChunkTypes.h
				ChunkTypes.cpp
				SessionModeTypes.h
				BaseChunk.h
            	BaseChunk.cpp 
				TimeChunk.h
				TimeChunk.cpp
				UDPChunk.h
				UDPChunk.cpp
				WAVChunk.h
				WAVChunkcpp
				)