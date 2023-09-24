#ifndef FFT_CHUNK_TESTS
#define FFT_CHUNK_TESTS

#include "doctest.h"
#include "FFTChunk.h"

TEST_CASE("FFTChunk Test") {

    // Constructor Parameters
    double dChunkSize = 512;
    double dSampleRate = 44100;
    uint64_t i64TimeStamp = 100000;
    unsigned uBits = 16;
    unsigned uNumBytes = 2;
    unsigned uNumChannels = 2;

    std::vector<int16_t> vu16ChannelOne;
    vu16ChannelOne.assign(dChunkSize, 1);
    std::vector<int16_t> vu16ChannelTwo;
    vu16ChannelTwo.assign(dChunkSize, 2);
    // All the above sum to bytes below - size of class
    BaseChunk baseChunk;
    // Size of header info, size of channels and size of base class
    unsigned uClassSize_bytes = 36 + dChunkSize * uNumChannels * uNumBytes + baseChunk.GetSize();

    // Lets just start by creating a FFTChunk
    FFTChunk FFTChunkTestClass(dChunkSize, dSampleRate, i64TimeStamp, uBits, uNumBytes, uNumChannels);
    FFTChunkTestClass.m_vvi16FFTChunks[0] = vu16ChannelOne;
    FFTChunkTestClass.m_vvi16FFTChunks[1] = vu16ChannelTwo;

    FFTChunk FFTChunkTestClassCopy_0;

    // We can also check the basic serialisation functionality
    auto pvcBaseChunkBytes = FFTChunkTestClass.Serialise();
    FFTChunkTestClassCopy_0.Deserialise(pvcBaseChunkBytes);


    SUBCASE("Checking base chunk functionality") {
        // And then that its type is basechunk
        CHECK(FFTChunkTestClass.GetChunkType() == ChunkType::FFTChunk);
        // Then lets ensure that the size of the data contained is 0 bytes
        CHECK(FFTChunkTestClass.GetSize() == uClassSize_bytes);
        // We can also check serialisation and deserialsaation
        CHECK(FFTChunkTestClass.IsEqual(FFTChunkTestClassCopy_0));
    }


    // With basic checks done, lets check the copy constructor works
    FFTChunk CopyOfFFTChunkTestClass = FFTChunkTestClass;


    SUBCASE("Checking copy constructors") {
        CHECK(FFTChunkTestClass.IsEqual(FFTChunkTestClass));
        // Now check if we change something in base class that the classes are no longer equal
        CopyOfFFTChunkTestClass.SetSourceIdentifier({ 1, 1 });
        CHECK(FFTChunkTestClass.IsEqual(CopyOfFFTChunkTestClass) == false);
    }


    auto JSONDocument = nlohmann::json();
    auto strChunkName = ChunkTypesNamingUtility::toString(ChunkType::FFTChunk);
    JSONDocument[strChunkName]["SourceIndentifierSize"] = std::to_string(0);
    JSONDocument[strChunkName]["SourceIndentifier"] = std::vector<uint8_t>();
    JSONDocument[strChunkName]["ChunkSize"] = std::to_string(dChunkSize);
    JSONDocument[strChunkName]["SampleRate"] = std::to_string(dSampleRate);
    JSONDocument[strChunkName]["TimeStamp"] = std::to_string(i64TimeStamp);
    JSONDocument[strChunkName]["uBits"] = std::to_string(uBits);
    JSONDocument[strChunkName]["NumBytes"] = std::to_string(uNumBytes);
    JSONDocument[strChunkName]["NumChannels"] = std::to_string(uNumChannels);
    JSONDocument[strChunkName]["Channels"][std::to_string(0)] = vu16ChannelOne;
    JSONDocument[strChunkName]["Channels"][std::to_string(1)] = vu16ChannelTwo;

    SUBCASE("Checking ToJSON Converter") {
        CHECK(*(FFTChunkTestClass.ToJSON()) == JSONDocument);
    }
}

#endif