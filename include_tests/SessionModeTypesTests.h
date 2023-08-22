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

}

#endif