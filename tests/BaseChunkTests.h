#ifndef BASE_CHUNK_TESTS
#define BASE_CHUNK_TESTS

#include "doctest.h"
#include "BaseChunk.h"

TEST_CASE("BaseChunk Test") {

    // Lets just start by creating a vanilla BaseChunk
    BaseChunk BaseChunkTestClass;

    SUBCASE("Checking base chunk functionality") {
        // And then that its type is basechunk
        CHECK(BaseChunkTestClass.GetChunkType() == ChunkType::ChunkBase);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(BaseChunkTestClass.GetSize() == 0);
    }

}

#endif