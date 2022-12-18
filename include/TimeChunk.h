#ifndef COMPLEX_TIME_CHUNK
#define COMPLEX_TIME_CHUNK

/*Standard Includes*/
#include <memory>
#include <vector>
#include <complex>

/*Custom Includes*/
#include "BaseChunk.h"

/**
 * @brief Complex Time Data Chunk used to store all samples data from the
 *          The active ADCs and their respective channels
 */
class TimeChunk : public BaseChunk
{
private:
public:
    double m_dChunkSize;                                            ///< Number of samples contained in a single chunk
    double m_dSampleRate;                                           ///< Sample rate used to obtain data in chunk
    double m_dTimeStamp;                                            ///< Timestamp of when chunk was taken
    unsigned m_uBits;                                               ///< Bits of ADC used to produce chunk
	unsigned m_uNumBytes;                                           ///< Number of bytes in single sample
    unsigned m_uNumChannels;                                        ///< Number of audio channels in chunk
    std::vector<std::vector<std::vector<float>>> m_vvvfTimeChunk;   ///< Vector of ADCChannelSamples corresponding to active ADCs

    /**
     * @brief Construct a new Base Chunk object
     * @param[in] dChunkSize The number of samples contained in each ADC channel chunk
     * @param[in] dSampleRate The sample rate used to generate all data within the chunk
     * @param[in] dTimeStamp The time the chunk was created
     * @param[in] uBits Bits of ADC used to produce chunk
     */
    TimeChunk(double dChunkSize, double dSampleRate, double dTimeStamp, unsigned uBits, unsigned uNumBytes);

    /**
     * @brief Construct a new Time Chunk object
     * @param[in] timeChunk pointer to time chunk
     */
    TimeChunk(const TimeChunk& timeChunk);
    TimeChunk(std::shared_ptr<TimeChunk> pTimeChunk);
    //~TimeChunk() {};

    /**
     * @brief Get the Chunk Type object
     * @return[in] ChunkType of chunk
     */
    ChunkType GetChunkType() override { return ChunkType::UDPChunk; };
};

#endif