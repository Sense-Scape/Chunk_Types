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
    std::vector<std::vector<uint16_t>> m_vvfTimeChunks;                ///< Vector of vectors corresponding to channel samples

    /**
     * @brief Construct a new Base Chunk object
     * @param[in] dChunkSize The number of samples contained in each ADC channel chunk
     * @param[in] dSampleRate The sample rate used to generate all data within the chunk
     * @param[in] dTimeStamp The time the chunk was created
     * @param[in] uBits Bits of ADC used to produce chunk
     * @param[in] uNumBytes Number of bytes in single sample
     * @param[in] uNumChannels Number of audio channels in chunk
     */
    TimeChunk(double dChunkSize, double dSampleRate, double dTimeStamp, unsigned uBits, unsigned uNumBytes, unsigned uNumChannels);

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
    ChunkType GetChunkType() override { return ChunkType::TimeChunk; };

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetSize() override;

    /**
     * @brief Fill a byte array the represents this object
     * @param[in] pByteArray Shared pointer to byte vector containing byte data
     */
    std::shared_ptr<std::vector<char>> Serialise() override;

    /**
     * @brief Converts byte array to object members
     * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
     */
    void Deserialise(std::shared_ptr<std::vector<char>> pBytes) override;
};

#endif