#ifndef CHUNK_TO_JSON_CONVERTER
#define CHUNK_TO_JSON_CONVERTER

/* Library Includes */
#include "json.hpp"

// Abstract class that enforces a ToJSON conversion for a chunk
class ChunkToJSONConverter {
public:
    // Pure virtual function for calculating the area
    virtual nlohmann::json ToJSON() const = 0;
};

#endif
