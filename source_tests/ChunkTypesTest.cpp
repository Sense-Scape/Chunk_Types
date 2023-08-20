#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

/*
*
	Every chunk gets allocated its own header file

	These are then inlcuded here and are built
	into an exectuable

	This should then be run to check the chunk
	functionality
*/
#include "SessionModeTypesTests.h"
#include "BaseChunkTests.h"
#include "TimeChunkTests.h"
#include "WAVChunkTests.h"
#include "JSONChunkTests.h"
#include "WatchdogChunkTests.h"