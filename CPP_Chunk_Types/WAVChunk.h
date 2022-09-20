#ifndef WAVCHUNK
#define WAVCHUNK

/*Standard Includes*/
#include <algorithm>

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

    /*
    * @brief Constructor
    */
    WAVChunk();
    WAVChunk(std::shared_ptr<WAVChunk> pWAVChunk);

    /*
    * @brief Returns the derived chunk type
    * @param[out] ChunkType of type WAVChunk
    */
    ChunkType GetChunkType() override { return ChunkType::WAVChunk; };

    /*
    * @brief unpacks WAV data into indivudal vectors of channel data
    * @param[in] pvvdUnpackedWAVData shared pointer to vector of vectors of doubles
    */
    void UnpackWAVData(std::shared_ptr<std::vector<std::vector<double>>> pvvdUnpackedWAVData);

    /*
    * @brief Converts an array of 44 chars in to WAVHeader structure
    * @param[out] returns a WAVHeader structure
    */
    static WAVHeader BytesToWAVHeader(std::vector<char>& vcWAVHeader);

    /*
    * @brief Converts a WAV header into a array of 44 chars 
    * @param[out] shared pointer to vector of byes
    */
    std::shared_ptr<std::vector<char>> WAVHeaderToBytes();

    /*
    * @brief Converts all little endian byte representation into partially big endian as per WAV header structure
    * @param[in] pointer to wav header bytes
    */
    static void FormatWAVHeaderBytes(std::shared_ptr<std::vector<char>> pvcWAVHeaderBytes);
};


#endif
