#ifndef FFT_CHUNK
#define FFT_CHUNK

/*Standard Includes*/
#include <memory>
#include <vector>
#include <complex>

/*Custom Includes*/
#include "BaseChunk.h"
#include "ChunkToJSONConverter.h"

/**
 * @brief Time Data Chunk used to store all samples data from the
 *          The active ADCs and their respective channels
 */
class FFTChunk : public BaseChunk,
    public ChunkToJSONConverter
{
public:
    double m_dChunkSize;                                            ///< Number of samples contained in a single chunk
    double m_dSampleRate;                                           ///< Sample rate used to obtain data in chunk
    uint64_t m_i64TimeStamp;                                        ///< Timestamp of when chunk was taken
    unsigned m_uNumChannels;                                        ///< Number of audio channels in chunk
    std::vector<std::vector<std::complex<float>>> m_vvcfFFTChunks; ///< Vector of vectors corresponding to channel samples

    /**
     * @brief Construct a new Base Chunk object
     */
    FFTChunk();

    /**
     * @brief Construct a new Base Chunk object
     * @param[in] dChunkSize The number of samples contained in each ADC channel chunk
     * @param[in] dSampleRate The sample rate used to generate all data within the chunk
     * @param[in] llTimeStamp The time the chunk was created
     * @param[in] uNumChannels Number of audio channels in chunk
     */
    FFTChunk(double dChunkSize, double dSampleRate, uint64_t i64TimeStamp, unsigned uNumChannels);

    /**
     * @brief Construct a new Time Chunk object
     * @param[in] FFTChunk pointer to time chunk
     */
    FFTChunk(const FFTChunk& FFTChunk);
    FFTChunk(std::shared_ptr<FFTChunk> pFFTChunk);

    /**
     * @brief Get the Chunk Type object
     * @return[in] ChunkType of chunk
     */
    ChunkType GetChunkType() override { return ChunkType::FFTChunk; };

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetSize() override;

    /**
     * @brief Fill a byte array the represents this object
     * @param[in] pByteArray Shared pointer to byte vector containing byte data
     */
    std::shared_ptr<std::vector<char>> Serialise();

    /**
     * @brief Converts byte array to object members
     * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
     */
    void Deserialise(std::shared_ptr<std::vector<char>> pBytes);

    /**
    * @brief Returns if the two classes are equal
    * @return Reference to the class with which we want to compare
    */
    bool IsEqual(FFTChunk& FFTChunk);

    /**
    * @brief Returns the JSON equivalent of this classes representation
    */
    std::shared_ptr<nlohmann::json> ToJSON() override;

protected:
    /**
     * @brief Fill a byte array the represents this object
     * @param[in] pByteArray Shared pointer to byte vector containing byte data
     */
    std::shared_ptr<std::vector<char>> GetInternalSerialisation();

private:

    /**
     * @brief Get the size of object in bytes
     * @return Size of object in bytes
     */
    unsigned GetInternalSize();

    /**
     * @brief Fills all channels with zeroed data
     */
    void InitialiseChannels();

    /**
    * @brief Converts a member channel of complex data to string <I,Q>
    * @param uChannelIndex the channel which shall be converted
    */
    std::string ConvertComplexChannelDataToString(uint16_t uChannelIndex);
};

#endif