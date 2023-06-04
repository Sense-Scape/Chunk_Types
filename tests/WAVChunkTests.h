#ifndef WAV_CHUNK_TESTS
#define WAV_CHUNK_TESTS

#include "doctest.h"
#include "WAVChunk.h"

TEST_CASE("WAVChunk Test") {

    // Lets just start by creating a vanilla BaseChunk
    uint64_t i64TimeStamp = 0;
    WAVChunk WAVChunkTestClass(i64TimeStamp);
    WAVHeader sWAVHeader;

    SUBCASE("Checking base chunk functionality") {
        // And then that its type is basechunk
        CHECK(WAVChunkTestClass.GetChunkType() == ChunkType::WAVChunk);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(WAVChunkTestClass.GetSize() == 2);
        // Checking default WAVHeader struct header
        CHECK(WAVChunkTestClass.m_sWAVHeader == sWAVHeader);
    }


    // Lets create some synthetic data
    std::vector<int16_t> vi16SyntheticData= { 1,0,1,0,1,0,1,0 };
    std::vector<double> vi16SyntheticDataChannelOne = { 1,1,1,1 };
    std::vector<double> vi16SyntheticDataChannelTwo = { 0,0,0,0 };
    // And set the data in the WAV Chunk class
    WAVChunkTestClass.m_vi16Data = vi16SyntheticData;
    WAVChunkTestClass.m_sWAVHeader.Subchunk2Size = vi16SyntheticData.size();
    WAVChunkTestClass.m_sWAVHeader.NumOfChan = 2;

    // Lets now unpack the data
    auto pvvdUnpackedData = std::make_shared<std::vector<std::vector<double>>>();
    WAVChunkTestClass.UnpackWAVData(pvvdUnpackedData);


    SUBCASE("Checking packing and unpacking of wav data") {
        // Checking if setting data works correctly
        CHECK(WAVChunkTestClass.m_vi16Data == vi16SyntheticData);
        // Checking if unpacking works as expected
        CHECK(pvvdUnpackedData->at(0) == vi16SyntheticDataChannelOne);
        CHECK(pvvdUnpackedData->at(1) == vi16SyntheticDataChannelTwo);
    }

    // Lets now check WAV header conversion
    auto a = WAVChunkTestClass.WAVHeaderToBytes();
    WAVHeader sWAVHeaderTwo = WAVChunk::BytesToWAVHeader(*a);


    SUBCASE("Checking WAV Header byte conversion") {
        // Checking if setting data works correctly
        CHECK(WAVChunkTestClass.m_sWAVHeader == sWAVHeaderTwo);
    }
}

#endif