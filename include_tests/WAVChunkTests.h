#ifndef WAV_CHUNK_TESTS
#define WAV_CHUNK_TESTS

#include "doctest.h"
#include "WAVChunk.h"

TEST_CASE("WAVChunk Test") {

    // Lets just start by creating a vanilla BaseChunk
    WAVChunk WAVChunkTestClass;
    WAVHeader sWAVHeader;
    // All the above sum to bytes below - size of class
    BaseChunk baseChunk;
    // Size of header info, size of channels and size of base class
    unsigned uClassSize_bytes = sizeof(WAVChunkTestClass.m_i64TimeStamp) + sizeof(sWAVHeader)  + baseChunk.GetSize();


    SUBCASE("Checking default class functionality") {
        // And then that its type is basechunk
        CHECK(WAVChunkTestClass.GetChunkType() == ChunkType::WAVChunk);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(WAVChunkTestClass.GetSize() == uClassSize_bytes);
        // Checking default WAVHeader struct header
        CHECK(WAVChunkTestClass.m_sWAVHeader == sWAVHeader);
    }


    // Lets create some synthetic data. A packed channela and 2 unpacked channels
    std::vector<int16_t> vi16SyntheticDataChannelOne = { 1,1,1,1 };
    std::vector<int16_t> vi16SyntheticDataChannelTwo = { 0,0,0,0 };
    std::vector<int16_t> vi16SyntheticData = { 1,0,1,0,1,0,1,0 };
    // And set the data in the WAV Chunk class
    WAVChunkTestClass.m_vi16Data = vi16SyntheticData;
    WAVChunkTestClass.m_sWAVHeader.Subchunk2Size = vi16SyntheticData.size();
    WAVChunkTestClass.m_sWAVHeader.NumOfChan = 2;
    // Lets now unpack the data
    auto pvvi16UnpackedData = std::make_shared<std::vector<std::vector<int16_t>>>();
    WAVChunkTestClass.UnpackWAVData(pvvi16UnpackedData);


    SUBCASE("Checking WAV data - packing, unpacking") {
        // Checking if setting data works correctly
        CHECK(WAVChunkTestClass.m_vi16Data == vi16SyntheticData);
        // Checking if unpacking work by checking channel one
        CHECK(pvvi16UnpackedData->at(0) == vi16SyntheticDataChannelOne);
        // And channel two
        CHECK(pvvi16UnpackedData->at(1) == vi16SyntheticDataChannelTwo);
    }


    // Generate a copy by reference
    WAVChunk WAVChunkTestClassCopy_0(WAVChunkTestClass);
    // And generate a copy using a shared pointer, this assumes the first test passes
    auto pWAVChunk = std::make_shared<WAVChunk>(WAVChunkTestClass);
    auto pWAVChunkCopy_0(pWAVChunk);
    // We can also check the WAV header conversion to bytes
    auto pvcWAVHeader_bytes = WAVChunkTestClass.WAVHeaderToBytes();
    WAVHeader sWAVHeaderDesrialised = WAVChunk::BytesToWAVHeader(*pvcWAVHeader_bytes);
    

    SUBCASE("Checking - copying, serialisation, deserialisation") {
        // Checking the copy constructor which uses the class reference
        CHECK(WAVChunkTestClass.IsEqual(WAVChunkTestClassCopy_0));
        // Checking the copy constructor which uses the class pointer
        CHECK(WAVChunkTestClass.IsEqual(*pWAVChunkCopy_0));
        // Checking if setting data works correctly
        CHECK(WAVChunkTestClass.m_sWAVHeader == sWAVHeaderDesrialised);
    }

    auto JSONDocument = nlohmann::json();
    auto strChunkName = ChunkTypesNamingUtility::toString(ChunkType::WAVChunk);
    JSONDocument[strChunkName]["SourceIndentifierSize"] = std::to_string(0);
    JSONDocument[strChunkName]["SourceIndentifier"] = std::vector<uint8_t>();
    JSONDocument[strChunkName]["WAVHeader"] = "ChunkSize: 0\nSubchunk1Size: 16\nAudioFormat: 1\nNumOfChan: 2\nSamplesPerSec: 0\nBytesPerSec: 0\nBlockAlign: 0\nBitsPerSample: 0\nSubchunk2Size: 8\n";
    JSONDocument[strChunkName]["ChunkSize"] = "70";
    JSONDocument[strChunkName]["TimeStamp"] = "0";
    JSONDocument[strChunkName]["VI16Data"] = "10101010";

    SUBCASE("Checking ToJSON Converter") {
        CHECK(*(WAVChunkTestClass.ToJSON()) == JSONDocument);
    }
}

#endif