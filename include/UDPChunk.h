#ifndef UDP_CHUNK
#define	UDP_CHUNK

/* Standard Includes */
#include <vector>

/* Custom Includes */
#include "BaseChunk.h"

/**
 * @brief UDP Data Chunk used to store UDP datagram data to pass between modules
 */
class UDPChunk : public BaseChunk
{

public:
    unsigned m_uChunkLength;                ///< Length of UDP data
    std::vector<char> m_vcDataChunk;        ///< Vector of UDP data

    /**
     * @brief Construct a new Time Chunk object
     * @param[in] uChunkLength bytes to store in UDP Chunk
     */
    UDPChunk(unsigned uChunkLength);
    UDPChunk(std::shared_ptr<UDPChunk> pUDPChunk);
    ~UDPChunk() {};

    /**
     * @brief Get the Chunk Type object
     * @return ChunkType Chunk type of the chunk
     */
    virtual ChunkType GetChunkType() override { return ChunkType::UDPChunk; };
};

#endif
