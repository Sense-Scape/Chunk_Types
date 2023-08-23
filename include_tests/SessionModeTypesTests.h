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


    


    unsigned uSequenceNumber = 1;						
    char cTransmissionState = 1;						
    unsigned uTransmissionSize = 1;					
    unsigned u32uChunkType = 1;						
    uint32_t uSessionNumber = 1;						
    std::vector<uint8_t> sUID = std::vector<uint8_t>({ 1,2,3,4,5,6 });
    unsigned uPreviousSequenceNumber = 0;														
    unsigned uPreviousSessionNumber = 0;														

    
    auto ReliableSessionSessionModeTestClass = ReliableSessionSessionMode();
    auto ReliableSessionSessionModeTestClassCopy = ReliableSessionSessionMode();
    unsigned uSessionModeSize = 31;

    ReliableSessionSessionModeTestClass.m_puSequenceNumber.second = uSequenceNumber;
    ReliableSessionSessionModeTestClass.m_pcTransmissionState.second = cTransmissionState;
    ReliableSessionSessionModeTestClass.m_puTransmissionSize.second = uTransmissionSize;
    ReliableSessionSessionModeTestClass.m_pu32uChunkType.second = u32uChunkType;
    ReliableSessionSessionModeTestClass.m_pusUID.second = sUID;
    ReliableSessionSessionModeTestClass.m_uPreviousSequenceNumber = uPreviousSequenceNumber;
    ReliableSessionSessionModeTestClass.m_uPreviousSessionNumber = uPreviousSessionNumber;

    ReliableSessionSessionModeTestClassCopy.m_puSequenceNumber.second = uSequenceNumber;
    ReliableSessionSessionModeTestClassCopy.m_pcTransmissionState.second = cTransmissionState;
    ReliableSessionSessionModeTestClassCopy.m_puTransmissionSize.second = uTransmissionSize;
    ReliableSessionSessionModeTestClassCopy.m_pu32uChunkType.second = u32uChunkType;
    ReliableSessionSessionModeTestClassCopy.m_pusUID.second = sUID;
    ReliableSessionSessionModeTestClassCopy.m_uPreviousSequenceNumber = uPreviousSequenceNumber;
    ReliableSessionSessionModeTestClassCopy.m_uPreviousSessionNumber = uPreviousSessionNumber;

    SUBCASE("Checking GetSize Equality test") {

        CHECK(ReliableSessionSessionModeTestClass.GetSize() == uSessionModeSize);

        CHECK(ReliableSessionSessionModeTestClass.IsEqual(ReliableSessionSessionModeTestClassCopy));
    }

}

#endif