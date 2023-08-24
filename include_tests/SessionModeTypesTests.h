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


    // Setting up session mode states
    unsigned uSequenceNumber = 1;						
    char cTransmissionState = 1;						
    unsigned uTransmissionSize = 1;					
    unsigned u32uChunkType = 1;						
    uint32_t uSessionNumber = 1;						
    std::vector<uint8_t> sUID = std::vector<uint8_t>({ 1,2,3,4,5,6 });
    unsigned uPreviousSequenceNumber = 0;														
    unsigned uPreviousSessionNumber = 0;														

    // Creating dummy classes
    auto ReliableSessionSessionModeTestClass = ReliableSessionSessionMode();
    auto ReliableSessionSessionModeTestClassCopy = ReliableSessionSessionMode();
    unsigned uSessionModeSize = 31;

    // Setting session states
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

    SUBCASE("GetSize Equality test") {

        CHECK(ReliableSessionSessionModeTestClass.GetSize() == uSessionModeSize);

        CHECK(ReliableSessionSessionModeTestClass.IsEqual(ReliableSessionSessionModeTestClassCopy));

    }


    // Attempting serialisation
    auto pvcBytes = ReliableSessionSessionModeTestClass.Serialise();
    auto ReliableSessionSessionModeTestSerialisationClass = ReliableSessionSessionMode();
    ReliableSessionSessionModeTestSerialisationClass.Deserialise(pvcBytes);


    SUBCASE("Serialisation test") {

        CHECK(ReliableSessionSessionModeTestClass.IsEqual(ReliableSessionSessionModeTestSerialisationClass));

    }


    auto ReliableSessionSessionModeTestIncrement= ReliableSessionSessionMode();
    

    SUBCASE("Incrementing sequence and session number tests") {

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSessionNumber.second == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSessionNumber == 0);

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 0);

        ReliableSessionSessionModeTestIncrement.IncrementSequence();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 0);

        ReliableSessionSessionModeTestIncrement.IncrementSequence();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 2);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 1);

        ReliableSessionSessionModeTestIncrement.IncrementSession();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSessionNumber.second == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSessionNumber == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 0);

        ReliableSessionSessionModeTestIncrement.IncrementSequence();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSessionNumber.second == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSessionNumber == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 0);

        ReliableSessionSessionModeTestIncrement.IncrementSequence();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSessionNumber.second == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSessionNumber == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 2);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 1);

        ReliableSessionSessionModeTestIncrement.IncrementSession();

        CHECK(ReliableSessionSessionModeTestIncrement.m_puSessionNumber.second == 2);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSessionNumber == 1);
        CHECK(ReliableSessionSessionModeTestIncrement.m_puSequenceNumber.second == 0);
        CHECK(ReliableSessionSessionModeTestIncrement.m_uPreviousSequenceNumber == 0);
    }
}

#endif