#include "FFTChunk.h"

FFTChunk::FFTChunk() :
    BaseChunk(),
    m_dChunkSize(0),
    m_dSampleRate(0),
    m_i64TimeStamp(0),
    m_uBits(0),
    m_uNumBytes(0),
    m_uNumChannels(0),
    m_vvi16FFTChunks()
{
    InitialiseChannels();
}

FFTChunk::FFTChunk(double dChunkSize, double dSampleRate, uint64_t i64TimeStamp, unsigned uBits, unsigned uNumBytes, unsigned uNumChannels) :
    BaseChunk(),
    m_dChunkSize(dChunkSize),
    m_dSampleRate(dSampleRate),
    m_i64TimeStamp(i64TimeStamp),
    m_uBits(uBits),
    m_uNumBytes(uNumBytes),
    m_uNumChannels(uNumChannels),
    m_vvi16FFTChunks()
{
    InitialiseChannels();
}

FFTChunk::FFTChunk(std::shared_ptr<FFTChunk> pFFTChunk) :
    BaseChunk(pFFTChunk)
{
    // untested
    m_dChunkSize = pFFTChunk->m_dChunkSize;
    m_dSampleRate = pFFTChunk->m_dSampleRate;
    m_i64TimeStamp = pFFTChunk->m_i64TimeStamp;
    m_uBits = pFFTChunk->m_uBits;
    m_uNumBytes = pFFTChunk->m_uNumBytes;
    m_uNumChannels = pFFTChunk->m_uNumChannels;
    m_vvi16FFTChunks = pFFTChunk->m_vvi16FFTChunks;
}

FFTChunk::FFTChunk(const FFTChunk& FFTChunk) :
    BaseChunk(FFTChunk)
{
    // untested
    m_dChunkSize = FFTChunk.m_dChunkSize;
    m_dSampleRate = FFTChunk.m_dSampleRate;
    m_i64TimeStamp = FFTChunk.m_i64TimeStamp;
    m_uBits = FFTChunk.m_uBits;
    m_uNumBytes = FFTChunk.m_uNumBytes;
    m_uNumChannels = FFTChunk.m_uNumChannels;
    m_vvi16FFTChunks = FFTChunk.m_vvi16FFTChunks;
}

unsigned FFTChunk::GetSize()
{
    return GetInternalSize();
}


unsigned FFTChunk::GetInternalSize()
{
    unsigned uByteSize = 0;

    // First check baseclass
    BaseChunk SelfBaseChunk = static_cast<BaseChunk&>(*this);
    uByteSize += SelfBaseChunk.GetSize();

    // Then this class
    uByteSize += sizeof(m_dChunkSize);
    uByteSize += sizeof(m_dSampleRate);
    uByteSize += sizeof(m_i64TimeStamp);
    uByteSize += sizeof(m_uBits);
    uByteSize += sizeof(m_uNumBytes);
    uByteSize += sizeof(m_uNumChannels);

    // Iterate over all elements of m_vvi16FFTChunks and infer type using auto
    for (const auto& vfFFTChunk : m_vvi16FFTChunks)
        uByteSize += sizeof(vfFFTChunk[0]) * vfFFTChunk.size();

    return uByteSize;
}

std::shared_ptr<std::vector<char>> FFTChunk::Serialise()
{
    return GetInternalSerialisation();
}

std::shared_ptr<std::vector<char>> FFTChunk::GetInternalSerialisation()
{
    auto pvBytes = std::make_shared<std::vector<char>>();
    pvBytes->resize(GetSize());
    char* pcBytes = pvBytes->data();

    // Copy base data
    auto pcvBaseBytes = BaseChunk::Serialise();
    unsigned uBaseClassSize = BaseChunk::GetSize();
    memcpy(pcBytes, &pcvBaseBytes->front(), uBaseClassSize);
    pcBytes += uBaseClassSize;


    // Converting members to bytes
    memcpy(pcBytes, &m_dChunkSize, sizeof(m_dChunkSize));
    pcBytes += sizeof(m_dChunkSize);

    memcpy(pcBytes, &m_dSampleRate, sizeof(m_dSampleRate));
    pcBytes += sizeof(m_dSampleRate);

    memcpy(pcBytes, &m_i64TimeStamp, sizeof(m_i64TimeStamp));
    pcBytes += sizeof(m_i64TimeStamp);

    memcpy(pcBytes, &m_uBits, sizeof(m_uBits));
    pcBytes += sizeof(m_uBits);

    memcpy(pcBytes, &m_uNumBytes, sizeof(m_uNumBytes));
    pcBytes += sizeof(m_uNumBytes);

    memcpy(pcBytes, &m_uNumChannels, sizeof(m_uNumChannels));
    pcBytes += sizeof(m_uNumChannels);

    // Converting vector to bytes
    for (const auto& vi16FFTChunk : m_vvi16FFTChunks)
    {
        unsigned uChunkSizeBytes = sizeof(vi16FFTChunk[0]) * vi16FFTChunk.size();
        memcpy(pcBytes, &vi16FFTChunk[0], uChunkSizeBytes);
        pcBytes += uChunkSizeBytes;
    }

    return pvBytes;
}

void FFTChunk::Deserialise(std::shared_ptr<std::vector<char>> pvBytes)
{
    // Fill in base data
    BaseChunk::Deserialise(pvBytes);

    char* pcBytes = pvBytes->data();
    pcBytes += BaseChunk::GetSize();

    // Converting members to bytes
    memcpy(&m_dChunkSize, pcBytes, sizeof(m_dChunkSize));
    pcBytes += sizeof(m_dChunkSize);

    memcpy(&m_dSampleRate, pcBytes, sizeof(m_dSampleRate));
    pcBytes += sizeof(m_dSampleRate);

    memcpy(&m_i64TimeStamp, pcBytes, sizeof(m_i64TimeStamp));
    pcBytes += sizeof(m_i64TimeStamp);

    memcpy(&m_uBits, pcBytes, sizeof(m_uBits));
    pcBytes += sizeof(m_uBits);

    memcpy(&m_uNumBytes, pcBytes, sizeof(m_uNumBytes));
    pcBytes += sizeof(m_uNumBytes);

    memcpy(&m_uNumChannels, pcBytes, sizeof(m_uNumChannels));
    pcBytes += sizeof(m_uNumChannels);

    // Reserving space for vector
    InitialiseChannels();

    // Filling data vector
    unsigned uSampleSize = sizeof(m_vvi16FFTChunks[0][0]);
    for (unsigned uChannelIndex = 0; uChannelIndex < m_uNumChannels; ++uChannelIndex) {
        for (unsigned uSampleIndex = 0; uSampleIndex < m_dChunkSize; uSampleIndex++)
        {
            memcpy(&m_vvi16FFTChunks[uChannelIndex][uSampleIndex], pcBytes, uSampleSize);
            pcBytes += uSampleSize;
        }
    }
}

bool FFTChunk::IsEqual(FFTChunk& FFTChunk)
{
    // We can compare base class
    auto SelfBaseChunk = static_cast<BaseChunk&>(*this);
    auto comparatorBaseChunk = static_cast<BaseChunk&>(FFTChunk);
    bool bBaseEqual = SelfBaseChunk.IsEqual(comparatorBaseChunk);

    // We can then compare FFTChunk paramerters
    bool bIsEqual = (
        (m_dChunkSize == FFTChunk.m_dChunkSize) &&
        (m_dSampleRate == FFTChunk.m_dSampleRate) &&
        (m_i64TimeStamp == FFTChunk.m_i64TimeStamp) &&
        (m_uBits == FFTChunk.m_uBits) &&
        (m_uNumBytes == FFTChunk.m_uNumBytes) &&
        (m_uNumChannels == FFTChunk.m_uNumChannels) &&
        (m_vvi16FFTChunks == FFTChunk.m_vvi16FFTChunks)
        );

    // Now we check base and derived classes are equal
    bIsEqual = (bBaseEqual && bIsEqual);

    return bIsEqual;
}


void FFTChunk::InitialiseChannels()
{
    m_vvi16FFTChunks.resize(m_uNumChannels);

    for (unsigned uChannelIndex = 0; uChannelIndex < m_uNumChannels; ++uChannelIndex)
        m_vvi16FFTChunks[uChannelIndex].resize(m_dChunkSize);
}

std::shared_ptr<nlohmann::json> FFTChunk::ToJSON()
{
    auto JSONDocument = nlohmann::json();
    auto strChunkName = ChunkTypesNamingUtility::toString(GetChunkType());

    // Adding in Basechunk fields
    JSONDocument[strChunkName]["SourceIndentifierSize"] = std::to_string(m_u16SourceIndentifierSize);
    JSONDocument[strChunkName]["SourceIndentifier"] = m_vu8SourceIdentifier;

    // Adding in FFTChunk fields
    JSONDocument[strChunkName]["ChunkSize"] = std::to_string(m_dChunkSize);
    JSONDocument[strChunkName]["SampleRate"] = std::to_string(m_dSampleRate);
    JSONDocument[strChunkName]["TimeStamp"] = std::to_string(m_i64TimeStamp);
    JSONDocument[strChunkName]["uBits"] = std::to_string(m_uBits);
    JSONDocument[strChunkName]["NumBytes"] = std::to_string(m_uNumBytes);
    JSONDocument[strChunkName]["NumChannels"] = std::to_string(m_uNumChannels);

    for (unsigned uChannelIndex = 0; uChannelIndex < m_uNumChannels; uChannelIndex++)
        JSONDocument[strChunkName]["Channels"][std::to_string(uChannelIndex)] = m_vvi16FFTChunks[uChannelIndex];

    return std::make_shared<nlohmann::json>(JSONDocument);
}