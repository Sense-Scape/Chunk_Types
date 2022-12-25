#ifndef CHUNK_TYPES_UTILITY
#define CHUNK_TYPES_UTILITY

/*Standard Includes*/
#include <iostream>
#include <memory>
#include <string>

/*Custom Includes*/
#include "BaseChunk.h"
#include "UDPChunk.h"   
#include "TimeChunk.h"
#include "WAVChunk.h"  

class ChunkTypesUtility
{
public:

    ChunkTypesUtility() {};
    ~ChunkTypesUtility() {};

    static std::string toString(ChunkType eChunkType)
    {
        switch (eChunkType)
        {
            case ChunkType::ChunkBase: return "ChunkBase";
            case ChunkType::UDPChunk:  return "UDPChunk";
            case ChunkType::TimeChunk: return "TimeChunk";
            case ChunkType::WAVChunk:  return "WAVChunk";

            default: return "Unknown Chunk";
        }
    }

    static uint32_t toU32(ChunkType eChunkType)
    {
        switch (eChunkType)
        {
        case ChunkType::ChunkBase: return 1;
        case ChunkType::UDPChunk:  return 2;
        case ChunkType::TimeChunk: return 3;
        case ChunkType::WAVChunk:  return 4;

        default: return 0; // error
        }
    }

    static std::shared_ptr<BaseChunk> DuplicateDerivedChunk(std::shared_ptr<BaseChunk> pBaseChunk)
    {
        switch (pBaseChunk->GetChunkType())
        {
            case ChunkType::ChunkBase: return std::make_shared<BaseChunk>(pBaseChunk);
            case ChunkType::UDPChunk:  return std::make_shared<UDPChunk>(std::static_pointer_cast<UDPChunk>(pBaseChunk));
            case ChunkType::TimeChunk: return std::make_shared<TimeChunk>(std::static_pointer_cast<TimeChunk>(pBaseChunk));
            case ChunkType::WAVChunk:  return std::make_shared<WAVChunk>(std::static_pointer_cast<WAVChunk>(pBaseChunk));

            default:
            {
                std::cout << std::string(__FUNCTION__) + ": Unknown chunk type \n";
                return std::make_shared<BaseChunk>(BaseChunk(pBaseChunk));
            }
        }
    }

};

#endif
