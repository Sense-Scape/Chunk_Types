#ifndef TEXT_CHUNK
#define	TEXT_CHUNK

/* Standard Includes */
#include <vector>

/* Custom Includes */
#include "BaseChunk.h"

/* Library Includes */
#include "json.hpp"

/**
 * @brief UDP Data Chunk used to store UDP datagram data to pass between modules
 */
class JSONChunk : public BaseChunk
{
public:
    nlohmann::json m_JSONDocument; ///< a JSON object to store all JSON data

    /**
     * @brief Construct a new Time Chunk object
     * @param[in] uChunkLength bytes to store in UDP Chunk
     */
    JSONChunk();
    JSONChunk(std::shared_ptr<JSONChunk> pJSONChunk);
    ~JSONChunk() {};

    /**
     * @brief Get the Chunk Type object
     * @return ChunkType Chunk type of the chunk
     */
    virtual ChunkType GetChunkType() override { return ChunkType::JSONChunk; };

    /**
    * @brief Returns if the two classes are equal
    * @return Reference to the class with which we want to compare
    */
    bool IsEqual(JSONChunk& jsonChunk);

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetSize() override;

    /**
     * @brief Fill a byte array the represents this object
     * @param[in] pByteArray Shared pointer to byte vector containing byte data
     */
    std::shared_ptr<std::vector<char>> Serialise() override;

    /**
     * @brief Converts byte array to object members
     * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
     */
    void Deserialise(std::shared_ptr<std::vector<char>> pBytes);

protected:
    /**
     * @brief Fill a byte array the represents this object
     * @param[in] pByteArray Shared pointer to byte vector containing byte data
     */
    std::shared_ptr<std::vector<char>> GetInternalSerialisation();

private:
    uint16_t m_JSONDocumentSize_bytes; ///< Size of json document only used during serialisation

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetInternalSize();
};

#endif
