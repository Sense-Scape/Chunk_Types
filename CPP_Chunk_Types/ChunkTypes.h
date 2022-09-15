#ifndef CHUNKTYPES
#define CHUNKTYPES

/*Standard Includes*/
#include <string>

/*Custom Includes*/


/*
* List of enumerated chunk types.
* 
* Sets of processing modules are either able to process particular chunk types
* or they are able to convert one chunk type to another and pass it on.
* 
* This allows for modules to be agnostic of what is before and after them in 
* the processing chain. 
*/

enum class ChunkType
{
    ChunkBase,
    UDPChunk,
    TimeChunk,
    WAVChunk
};

class ChunkTypeStrings
{
public:

    ChunkTypeStrings() {};
    ~ChunkTypeStrings() {};

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
};

#endif