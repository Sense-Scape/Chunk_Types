#ifndef CHUNK_DUPLICATOR_UTILITY
#define CHUNK_DUPLICATOR_UTILITY

#include "BaseChunk.h"
#include "UDPChunk.h"   
#include "TimeChunk.h"
#include "WAVChunk.h"  
#include "WatchdogChunk.h"

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

        default:
            {
                std::cout << std::string(__FUNCTION__) + ": Unknown chunk type \n";
                return std::make_shared<BaseChunk>(BaseChunk(pBaseChunk));
            }
        }
    }
}

#endif
