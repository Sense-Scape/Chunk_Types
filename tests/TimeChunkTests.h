#ifndef TIME_CHUNK_TESTS
#define TIME_CHUNK_TESTS

#include "doctest.h"
#include "TimeChunk.h"

TEST_CASE("BaseChunk Test") {

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


    SUBCASE("Checking copy constructors") {
        bool bCopyCorrect =
            (
                (CopyOfTimeChunkTestClass.m_dChunkSize == TimeChunkTestClass.m_dChunkSize) &&
                (CopyOfTimeChunkTestClass.m_dSampleRate == TimeChunkTestClass.m_dSampleRate) &&
                (CopyOfTimeChunkTestClass.m_i64TimeStamp == TimeChunkTestClass.m_i64TimeStamp) &&
                (CopyOfTimeChunkTestClass.m_uBits == TimeChunkTestClass.m_uBits) &&
                (CopyOfTimeChunkTestClass.m_uNumBytes == TimeChunkTestClass.m_uNumBytes) &&
                (CopyOfTimeChunkTestClass.m_uNumChannels == TimeChunkTestClass.m_uNumChannels) &&
                (CopyOfTimeChunkTestClass.m_vvi16TimeChunks == TimeChunkTestClass.m_vvi16TimeChunks)
            );
        // With the copy complete, lets check if all the elements were correctly copied
        CHECK(bCopyCorrect == true);
    }
    

    // We shall now start to test the serialisation function
    std::shared_ptr<std::vector<char>> pBytes = TimeChunkTestClass.Serialise();
    TimeChunk DeserialisedTimeChunkTestClass(0,0,0,0,0,0);
    // Now convert the bytes back to the class
    DeserialisedTimeChunkTestClass.Deserialise(pBytes);


    SUBCASE("Checking desrialisation functionality") {
        bool bDeserialiseCorrect =
            (
                (CopyOfTimeChunkTestClass.m_dChunkSize == TimeChunkTestClass.m_dChunkSize) &&
                (CopyOfTimeChunkTestClass.m_dSampleRate == TimeChunkTestClass.m_dSampleRate) &&
                (CopyOfTimeChunkTestClass.m_i64TimeStamp == TimeChunkTestClass.m_i64TimeStamp) &&
                (CopyOfTimeChunkTestClass.m_uBits == TimeChunkTestClass.m_uBits) &&
                (CopyOfTimeChunkTestClass.m_uNumBytes == TimeChunkTestClass.m_uNumBytes) &&
                (CopyOfTimeChunkTestClass.m_uNumChannels == TimeChunkTestClass.m_uNumChannels) &&
                (CopyOfTimeChunkTestClass.m_vvi16TimeChunks == TimeChunkTestClass.m_vvi16TimeChunks)
                );
        // With the copy complete, lets check if all the elements were correctly copied
        CHECK(bDeserialiseCorrect == true);
    }
}

#endif