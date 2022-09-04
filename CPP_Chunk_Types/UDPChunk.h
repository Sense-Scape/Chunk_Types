#ifndef UDPCHUNK
#define	UDPCHUNK

/*Standard Includes*/
#include <vector>

/*Custom Includes*/
#include "BaseChunk.h"

/**
 * @brief UDP Data Chunk used to store UDP datagram data to pass between modules
 */
class UDPChunk : public BaseChunk
{

public:
    unsigned m_uChunkLength;      ///< Length of UDP data
    std::vector<char> m_cvDataChunk;  ///< Vector of UDP data

    /**
     * @brief Construct a new Time Chunk object
     *
     * @param timeChunk
     */
    UDPChunk(unsigned uChunkLength);
    ~UDPChunk() {};

    /**
     * @brief Get the Chunk Type object
     *
     * @return ChunkType
     */
    ChunkType getChunkType() override { return ChunkType::UDPChunk; };
};

#endif