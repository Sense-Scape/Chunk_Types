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
public:
    /**
     * @brief Default constructor for a new Base Chunk object
     * @param[in] vu8SourceIdentifier vector that stores the source identifier
     */
    BaseChunk(std::vector<uint8_t> vu8SourceIdentifier);
    BaseChunk(std::shared_ptr<BaseChunk> pBaseChunk);
    BaseChunk();

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
    virtual unsigned GetSize();

    /**
     * @brief Fill a byte array the represents this object
     * @return pvBytes Shared pointer to byte array that shall be filled
     */
    virtual std::shared_ptr<std::vector<char>> Serialise();

    /**
     * @brief Converts byte array to object members
     * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
     */
    void Deserialise(std::shared_ptr<std::vector<char>> pvBytes);

    /**
     * @brief Sets the source identifer of class
     * @param[in] vu8SourceIdentifier vector of uint8_t of the new source identifer
     */
    void SetSourceIdentifier(std::vector<uint8_t> vu8SourceIdentifier);

    /**
     * @brief Returns the source identifer of class
     * @return Vector of uint8_t of the source identifer
     */
    std::vector<uint8_t> GetSourceIdentifier();

    /**
     * @brief Returns if the two classes are equal
     * @return Reference to the class with which we want to compare
     */
    bool IsEqual(BaseChunk& baseChunk);

protected:
    /**
     * @brief Fill a byte array the represents this object
     * @return pvBytes Shared pointer to byte array that shall be filled
     */
    std::shared_ptr<std::vector<char>> GetInternalSerialisation();
private:
    uint16_t m_u16SourceIndentifierSize;        ///< Size of unique identifier
    std::vector<uint8_t> m_vu8SourceIdentifier; ///< Source identifier of the chunk

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetInternalSize();
};

#endif
