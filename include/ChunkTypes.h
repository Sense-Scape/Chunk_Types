#ifndef CHUNK_TYPES
#define CHUNK_TYPES

/* Standard Includes */
#include <string>

/* Custom Includes */

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
    WAVChunk,
    WatchdogChunk,
    JSONChunk,
    FFTChunk,
    FFTMagnitudeChunk,
};

#endif
