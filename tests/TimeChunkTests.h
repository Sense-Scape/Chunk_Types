#ifndef TIME_CHUNK_TESTS
#define TIME_CHUNK_TESTS

#include "doctest.h"
#include "TimeChunk.h"

TEST_CASE("TimeChunk Test") {

    // Constructor Parameters
    double dChunkSize = 256;
    double dSampleRate = 44100;
    uint64_t i64TimeStamp = 100000;
    unsigned uBits = 16;
    unsigned uNumBytes = 2;
    unsigned uNumChannels = 4;
    
    // All the above sum to bytes below
    unsigned uClassSize_bytes = 36;

    // Lets just start by creating a vanilla BaseChunk
    TimeChunk TimeChunkTestClass(dChunkSize, dSampleRate, i64TimeStamp, uBits, uNumBytes, uNumChannels);
    // Lets also create a vanilla BaseChunk
    BaseChunk BaseChunkTestClass;

    // We can also give the same identifier for both classes
    std::vector<uint8_t> vu8SourceIdentifier = { 255,255 };
    TimeChunkTestClass.SetSourceIdentifier(vu8SourceIdentifier);
    BaseChunkTestClass.SetSourceIdentifier(vu8SourceIdentifier);
    uClassSize_bytes += BaseChunkTestClass.GetSize();
    

    SUBCASE("Checking base chunk functionality") {
        // And then that its type is basechunk
        CHECK(TimeChunkTestClass.GetChunkType() == ChunkType::TimeChunk);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(TimeChunkTestClass.GetSize() == uClassSize_bytes);
    }


    // We can now simulate some data and check that the get size function still works
    unsigned uSimulatedChannelCount = 4;
    TimeChunkTestClass.m_vvi16TimeChunks.resize(uSimulatedChannelCount);
    for (unsigned uChannelIndex  = 0; uChannelIndex < uSimulatedChannelCount; uChannelIndex++)
        TimeChunkTestClass.m_vvi16TimeChunks[uChannelIndex].resize(dChunkSize);
    // Now update the expected class size
    uClassSize_bytes += uSimulatedChannelCount * dChunkSize * sizeof(uint16_t);


    SUBCASE("Checking getSize with variable size data") {
        // Lets verify that the class size is still correct
        CHECK(TimeChunkTestClass.GetSize() == uClassSize_bytes);
    }


    // With basic checks done, lets check the copy constructor works
    TimeChunk CopyOfTimeChunkTestClass = TimeChunkTestClass;


    SUBCASE("Checking copy constructors") 
    {
        CHECK(TimeChunkTestClass.IsEqual(TimeChunkTestClass));

        // Now do a simple check if we change something in base class the 
        // classes are no longer equal
        CopyOfTimeChunkTestClass.SetSourceIdentifier({ 1, 1 });
        CHECK(TimeChunkTestClass.IsEqual(CopyOfTimeChunkTestClass) == false);
    }
    

    // We shall now start to test the serialisation function
    std::shared_ptr<std::vector<char>> pBytes = TimeChunkTestClass.Serialise();
    TimeChunk DeserialisedTimeChunkTestClass(0,0,0,0,0,0);
    // Now convert the bytes back to the class
    DeserialisedTimeChunkTestClass.Deserialise(pBytes);


    SUBCASE("Checking de/serialisation functionality") {
        // Check the base class first
        CHECK(static_cast<BaseChunk&>(DeserialisedTimeChunkTestClass).IsEqual(static_cast<BaseChunk&>(TimeChunkTestClass)));
        // With the copy complete, lets check if all the elements were correctly copied
        CHECK(DeserialisedTimeChunkTestClass.IsEqual(TimeChunkTestClass));
    }
}

#endif