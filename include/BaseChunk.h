#ifndef BASECHUNK
#define BASECHUNK

/*Standard Includes*/
#include <memory>
#include <stdint.h>
#include <vector>
#include <cstring> // for memcpy

/*Custom Includes*/
#include "ChunkTypes.h"

/**
 * @brief BaseChunk used to store the basic data storage component meta-data
 */
class BaseChunk
{

private:

public:
    /**
     * @brief Default constructor for a new Base Chunk object
     *
     */
    BaseChunk();
    BaseChunk(std::shared_ptr<BaseChunk> pBaseChunk);

    /**
     * @brief Construct a new Base Chunk object
     *
     * @param baseChunk Reference to another BaseChunk
     */
    BaseChunk(const BaseChunk& baseChunk);

    virtual ~BaseChunk() {};

    /**
     * @brief Get the Type object
     *
     * @return ChunkType ChunkType of chunk
     */
    virtual ChunkType GetChunkType() { return ChunkType::ChunkBase; };
};

#endif