#ifndef CHUNK_DUPLICATOR_UTILITY_TESTS
#define CHUNK_DUPLICATOR_UTILITY_TESTS

#include "doctest.h"
#include "ChunkDuplicatorUtility.h"

TEST_CASE("Chunk Duplicator Utility Test") {

	// Create a JSON Chunk
	auto pJSONChunk = std::make_shared<JSONChunk>();
	pJSONChunk->m_JSONDocument["test"] = "confirmed";
	auto pcJSONBytes = pJSONChunk->Serialise();

	// Try Duplicate it using the duplicator utility
	auto pJSONDuplicatedChunk = ChunkDuplicatorUtility::DeserialiseDerivedChunk(pcJSONBytes, ChunkType::JSONChunk);
	pJSONDuplicatedChunk = std::static_pointer_cast<JSONChunk>(pJSONDuplicatedChunk);

	SUBCASE("Chunk Duplicator test") {
		CHECK(pJSONDuplicatedChunk == pJSONChunk);
	}
}

#endif