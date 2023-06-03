#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

/*
* 
	Every chunk gets allocated its own header file

	These are then inlcuded here and are built 
	into an exectuable

	This should then be run to check the chunk 
	functionality

	TODO: Move RULES it Obsidian

	Rules:
	> All test cases shall be seperated by two empty lines

*/
#include "BaseChunkTests.h"
#include "TimeChunkTests.h"
