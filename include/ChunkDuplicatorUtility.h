#ifndef CHUNK_DUPLICATOR_UTILITY
#define CHUNK_DUPLICATOR_UTILITY

#include "BaseChunk.h"
#include "UDPChunk.h"   
#include "TimeChunk.h"
#include "WAVChunk.h"  
#include "WatchdogChunk.h"
#include "JSONChunk.h"

class ChunkDuplicatorUtility
{
public:

    static std::shared_ptr<BaseChunk> DuplicateDerivedChunk(std::shared_ptr<BaseChunk> pBaseChunk)
    {
        switch (pBaseChunk->GetChunkType())
        {
        case ChunkType::ChunkBase: return std::make_shared<BaseChunk>(pBaseChunk);
        case ChunkType::UDPChunk:  return std::make_shared<UDPChunk>(std::static_pointer_cast<UDPChunk>(pBaseChunk));
        case ChunkType::TimeChunk: return std::make_shared<TimeChunk>(std::static_pointer_cast<TimeChunk>(pBaseChunk));
        case ChunkType::WAVChunk:  return std::make_shared<WAVChunk>(std::static_pointer_cast<WAVChunk>(pBaseChunk));
        case ChunkType::WatchdogChunk:  return std::make_shared<WatchdogChunk>(std::static_pointer_cast<WatchdogChunk>(pBaseChunk));
        case ChunkType::JSONChunk:  return std::make_shared<JSONChunk>(std::static_pointer_cast<JSONChunk>(pBaseChunk));

        default:
        {
            std::cout << std::string(__FUNCTION__) + ": Unknown chunk type \n";
            return std::make_shared<BaseChunk>(BaseChunk(pBaseChunk));
        }
        }
    }

    static std::shared_ptr<BaseChunk> DeserialiseDerivedChunk(std::shared_ptr<std::vector<char>> pBytes, ChunkType eChunkType)
    {
        std::shared_ptr<BaseChunk> pChunk; // Declare the variable once

        switch (eChunkType)
        {
        case ChunkType::ChunkBase:
            pChunk = std::make_shared<BaseChunk>();
            break;
        case ChunkType::TimeChunk:
            pChunk = std::make_shared<TimeChunk>();
            break;
        case ChunkType::WAVChunk:
            pChunk = std::make_shared<WAVChunk>();
            break;
        case ChunkType::JSONChunk:
            pChunk = std::make_shared<JSONChunk>();
            break;
        default:
            std::cout << std::string(__FUNCTION__) + ": Unknown chunk type \n";
            pChunk = std::make_shared<BaseChunk>();
            break;
        }

        pChunk->Deserialise(pBytes);
        return pChunk;
    }
};

#endif
