#ifndef WAVCHUNK
#define WAVCHUNK

/*Standard Includes*/

/*Custom Includes*/
#include "BaseChunk.h"

typedef struct WAVHeader
{
    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4] = { 'R', 'I', 'F', 'F' }; // RIFF Header Magic header - BigEndian
    uint32_t ChunkSize;                     // RIFF Chunk Size - LittleEndian  - size of whole file in bytes minus 8 bytes
    uint8_t WAVE[4] = { 'W', 'A', 'V', 'E' }; // WAVE Header - BigEndian
    /* "fmt" sub-chunk */
    uint8_t fmt[4] = { 'f', 'm', 't', ' ' }; // FMT header - BigEndian
    uint32_t Subchunk1Size = 16;           // Size of the fmt chunk - BigEndian
    uint16_t AudioFormat = 1;              // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM - LittleEndian - 1 as there is no quantization
    uint16_t NumOfChan;                    // Number of channels 1=Mono 2=Sterio - LittleEndian
    uint32_t SamplesPerSec;                // Sampling Frequency in Hz - LittleEndian
    uint32_t bytesPerSec;                  // bytes per second - LittleEndian - " == SampleRate * NumChannels * BitsPerSample/8"
    uint16_t blockAlign;                   // 2=16-bit mono, 4=16-bit stereo - LittleEndian
    uint16_t bitsPerSample;                // Number of bits per sample - LittleEndian
    /* "data" sub-chunk */
    uint8_t Subchunk2ID[4] = { 'd', 'a', 't', 'a' }; // "data"  string - BigEndian
    uint32_t Subchunk2Size;                        // Sampled data length - LittleEndian
    // The following data - LittleEndian
} WAVHeader;


class WAVChunk :
    public BaseChunk
{
private:

public:
    WAVHeader m_sWAVHeader;
    std::vector<double> m_vdData;

    WAVChunk();

    ChunkType getChunkType() override { return ChunkType::WAVChunk; };

    static WAVHeader BytesToWAVHeader(std::vector<char>& vcWAVHeader);
};


#endif
