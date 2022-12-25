
# Min CMake version
cmake_minimum_required(VERSION 3.20)

idf_component_register(SRCS "BaseChunk.cpp" 
						"TimeChunk.cpp" 
						"UDPChunk.cpp"
						"WAVChunk.cpp"
						INCLUDE_DIRS "./include"
						)
