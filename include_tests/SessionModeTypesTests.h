#ifndef SESSION_MODE_TYPES_TESTS
#define SESSION_MODE_TYPES_TESTS

#include "doctest.h"
#include "SessionModeTypes.h"

TEST_CASE("Session Mode Types Test") {

	auto SessionModeBaseTestClass = SessionModeBase();


    SUBCASE("Base Session test") {
        // And then that its type is JSONchunk
        CHECK(SessionModeBaseTestClass.GetSessionType() == SessionModeType::SessionModeBase);
    }


    auto ReliableSessionSessionModeTestClass = ReliableSessionSessionMode();

    
    uint32_t u32SessionNumber = 1;
    char cTransmissionState = 0;
    unsigned uTransmissionSize = 512;
    unsigned uChunkType = 1;
    unsigned uSequenceNumber = 1;
    std::vector<uint8_t> vu8UID = {255, 255, 255, 100, 100, 100};
    std::vector<char> vcDataChunk;

    vcDataChunk.resize(sizeof(u32SessionNumber) + sizeof(cTransmissionState) +
        sizeof(uTransmissionSize) + sizeof(uChunkType) +
        sizeof(uSequenceNumber) + vu8UID.size() * sizeof(uint16_t));

    char* ptr = vcDataChunk.data();

    memcpy(ptr, &u32SessionNumber, sizeof(u32SessionNumber));
    ptr += sizeof(u32SessionNumber);

    memcpy(ptr, &cTransmissionState, sizeof(cTransmissionState));
    ptr += sizeof(cTransmissionState);

    memcpy(ptr, &uTransmissionSize, sizeof(uTransmissionSize));
    ptr += sizeof(uTransmissionSize);

    memcpy(ptr, &uChunkType, sizeof(uChunkType));
    ptr += sizeof(uChunkType);

    memcpy(ptr, &uSequenceNumber, sizeof(uSequenceNumber));
    ptr += sizeof(uSequenceNumber);

    for (const uint8_t& value : vu8UID) {
        memcpy(ptr, &value, sizeof(value));
        ptr += sizeof(value);
    }

  
    auto pUDPChunk = std::make_shared<UDPChunk>(512);
    pUDPChunk->m_vcDataChunk = vcDataChunk;
    ReliableSessionSessionModeTestClass.ConvertBytesToStates(pUDPChunk);


    SUBCASE("Base Session test") {
        // And then that its type is JSONchunk
        CHECK(ReliableSessionSessionModeTestClass.GetSessionType() == SessionModeType::ReliableSessionSessionMode);

        CHECK(ReliableSessionSessionModeTestClass.m_pcTransmissionState.second == cTransmissionState);
        CHECK(ReliableSessionSessionModeTestClass.m_puTransmissionSize.second == uTransmissionSize);
        CHECK(ReliableSessionSessionModeTestClass.m_pu32uChunkType.second == uChunkType);
        CHECK(ReliableSessionSessionModeTestClass.m_puSessionNumber.second == u32SessionNumber);
        CHECK(ReliableSessionSessionModeTestClass.m_pusUID.second == vu8UID);
    }

}

#endif