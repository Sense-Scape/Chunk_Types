#ifndef WAV_CHUNK_TESTS
#define WAV_CHUNK_TESTS

#include "doctest.h"
#include "WAVChunk.h"

TEST_CASE("WAVChunk Test") {

    // Lets just start by creating a vanilla BaseChunk
    WAVChunk BaseChunkTestClass;

    SUBCASE("Checking base chunk functionality") {
        // And then that its type is basechunk
        CHECK(BaseChunkTestClass.GetChunkType() == ChunkType::WAVChunk);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(BaseChunkTestClass.GetSize() == 0);
    }

}

#endif