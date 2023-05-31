#ifndef BASE_CHUNK_TESTS
#define BASE_CHUNK_TESTS

#include "doctest.h"
#include "BaseChunk.h"

TEST_CASE("Testing construction of BaseChunk") {
    
    // Lets just start by creating a vanilla BaseChunk
    BaseChunk BasechunkTestClass;

    // Then lets ensure that the size of the data contained is 0 bytes
    CHECK(BasechunkTestClass.GetSize() == 0);
    // And then that its type is basechunk
    CHECK(BasechunkTestClass.GetChunkType() == ChunkType::ChunkBase);
}

#endif