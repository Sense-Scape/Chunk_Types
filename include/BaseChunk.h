#ifndef BASE_CHUNK
#define BASE_CHUNK

/* Standard Includes */
#include <memory>
#include <stdint.h>
#include <vector>
#include <cstring> // for memcpy
#include <iostream>

/* Custom Includes */
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
     */
    BaseChunk() {};
    BaseChunk(std::shared_ptr<BaseChunk> pBaseChunk);

    /**
     * @brief Construct a new Base Chunk object
     * @param[in] baseChunk Reference to another BaseChunk
     */
    BaseChunk(const BaseChunk& baseChunk);

    virtual ~BaseChunk() {};

    /**
     * @brief Get the Type object
     * @return ChunkType ChunkType of chunk
     */
    virtual ChunkType GetChunkType() { return ChunkType::ChunkBase; };

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    virtual unsigned GetSize() {return 0;}; //TODO: Make this required "=0"

    /**
     * @brief Fill a byte array the represents this object
     * @return pvBytes Shared pointer to byte array that shall be filled
     */
    virtual std::shared_ptr<std::vector<char>> Serialise() {auto p = std::make_shared<std::vector<char>>(); return p;}; //TODO: Make this required "=0"

    /**
     * @brief Converts byte array to object members
     * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
     */
    virtual void Deserialise(std::shared_ptr<std::vector<char>> pBytes) {};
};

#endif
