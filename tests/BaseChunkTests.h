#ifndef BASE_CHUNK_TESTS
#define BASE_CHUNK_TESTS

#include "doctest.h"
#include "BaseChunk.h"

TEST_CASE("BaseChunk Test") {

    // Lets just start by creating a vanilla BaseChunk
    BaseChunk BaseChunkTestClass;


    SUBCASE("Checking base chunk default constructor") {
        // And then that its type is basechunk
        CHECK(BaseChunkTestClass.GetChunkType() == ChunkType::ChunkBase);
        // Then lets ensure that the size of the data contained is 2 bytes
        CHECK(BaseChunkTestClass.GetSize() == 2);
    }


    // Lets now give the device a unique identifier and see if the size if correct
    std::vector<uint8_t> vu8Indentidier = { 255, 255, 255 };
    BaseChunkTestClass.SetSourceIdentifier(vu8Indentidier);


    SUBCASE("Checking base set set source identifier (to verify size changes)") {
        // Then lets ensure that the size of the data contained is 2 bytes
        CHECK(BaseChunkTestClass.GetSize() == 5);
        // We can also check if the vector was set correctly
        CHECK(BaseChunkTestClass.GetSourceIdentifier() == vu8Indentidier);
    }

    // Checking copy constructors
    BaseChunk ReferenceCopyBaseChunkTestClass(BaseChunkTestClass);
    std::shared_ptr<BaseChunk> pBaseChunkTestClass = std::make_shared<BaseChunk>(BaseChunkTestClass);
    auto pPointerCopyBaseChunkTestClass(pBaseChunkTestClass);


    SUBCASE("Checking reference copy constructors") {
        CHECK(BaseChunkTestClass.IsEqual(ReferenceCopyBaseChunkTestClass));
        CHECK(BaseChunkTestClass.IsEqual(*pPointerCopyBaseChunkTestClass));
    }

    // Checking de.serialisation
    BaseChunk DeserialisedBaseChunkTestClass;
    std::shared_ptr<std::vector<char>> pBytes = BaseChunkTestClass.Serialise();
    DeserialisedBaseChunkTestClass.Deserialise(pBytes);


    SUBCASE("Checking De/Serialisation functionality") {
        CHECK(BaseChunkTestClass.IsEqual(DeserialisedBaseChunkTestClass));
    }

}

#endif