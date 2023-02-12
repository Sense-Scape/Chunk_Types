#include "TimeChunk.h"

TimeChunk::TimeChunk(double dChunkSize, double dSampleRate, double dTimeStamp, unsigned uBits, unsigned uNumBytes, unsigned uNumChannels) :
BaseChunk(),
m_dChunkSize(dChunkSize),
m_dSampleRate(dSampleRate),
m_dTimeStamp(dTimeStamp),
m_uBits(uBits),
m_uNumBytes(uNumBytes),
m_uNumChannels(uNumChannels)
{
}

TimeChunk::TimeChunk(std::shared_ptr<TimeChunk> pTimeChunk)
{
    // untested
    m_dChunkSize = pTimeChunk->m_dChunkSize;
    m_dSampleRate = pTimeChunk->m_dSampleRate;
    m_dTimeStamp = pTimeChunk->m_dTimeStamp;
    m_uBits = pTimeChunk->m_uBits;
    m_uNumBytes = pTimeChunk->m_uNumBytes;
    m_uNumChannels = pTimeChunk->m_uNumChannels;
    m_vvi16TimeChunks = pTimeChunk->m_vvi16TimeChunks;
}

TimeChunk::TimeChunk(const TimeChunk& timeChunk) : BaseChunk()
{
    // untested
    m_dChunkSize = timeChunk.m_dChunkSize;
    m_dSampleRate = timeChunk.m_dSampleRate;
    m_dTimeStamp = timeChunk.m_dTimeStamp;
    m_uBits = timeChunk.m_uBits;
    m_uNumBytes = timeChunk.m_uNumBytes;
    m_uNumChannels = timeChunk.m_uNumChannels;
    m_vvi16TimeChunks = timeChunk.m_vvi16TimeChunks;
}

unsigned TimeChunk::GetSize() 
{
    unsigned uByteSize = 0;

    uByteSize += sizeof(m_dChunkSize);
    uByteSize += sizeof(m_dSampleRate);
    uByteSize += sizeof(m_dTimeStamp);
    uByteSize += sizeof(m_uBits);
    uByteSize += sizeof(m_uNumBytes);
    uByteSize += sizeof(m_uNumChannels);

    // Iterate over all elements of m_vvi16TimeChunks and infer type using auto
    for (const auto& vfTimeChunk : m_vvi16TimeChunks) 
        uByteSize += sizeof(vfTimeChunk[0]) * vfTimeChunk.size();

    return uByteSize;
}

std::shared_ptr<std::vector<char>> TimeChunk::Serialise()
{
    auto pvBytes = std::make_shared<std::vector<char>>();
    pvBytes->resize(GetSize());
    char* pcBytes = pvBytes->data();

    // Converting members to bytes
    memcpy(pcBytes, &m_dChunkSize, sizeof(m_dChunkSize));
    pcBytes += sizeof(m_dChunkSize);

    memcpy(pcBytes, &m_dSampleRate, sizeof(m_dSampleRate));
    pcBytes += sizeof(m_dSampleRate);

    memcpy(pcBytes, &m_dTimeStamp, sizeof(m_dTimeStamp));
    pcBytes += sizeof(m_dTimeStamp);

    memcpy(pcBytes, &m_uBits, sizeof(m_uBits));
    pcBytes += sizeof(m_uBits);

    memcpy(pcBytes, &m_uNumBytes, sizeof(m_uNumBytes));
    pcBytes += sizeof(m_uNumBytes);

    memcpy(pcBytes, &m_uNumChannels, sizeof(m_uNumChannels));
    pcBytes += sizeof(m_uNumChannels);

    // Converting vector to bytes
    for (const auto& vfTimeChunk : m_vvi16TimeChunks) 
    {
        unsigned uChunkSizeBytes = sizeof(vfTimeChunk[0]) * vfTimeChunk.size();
        memcpy(pcBytes, &vfTimeChunk[0], uChunkSizeBytes);
        pcBytes += uChunkSizeBytes;
    }
    
    return pvBytes;
}

void TimeChunk::Deserialise(std::shared_ptr<std::vector<char>> pvBytes)
{
    char* pcBytes = pvBytes->data();

    // Converting members to bytes
    memcpy(&m_dChunkSize, pcBytes, sizeof(m_dChunkSize));
    pcBytes += sizeof(m_dChunkSize);

    memcpy( &m_dSampleRate, pcBytes, sizeof(m_dSampleRate));
    pcBytes += sizeof(m_dSampleRate);

    memcpy(&m_dTimeStamp, pcBytes, sizeof(m_dTimeStamp));
    pcBytes += sizeof(m_dTimeStamp);

    memcpy(&m_uBits, pcBytes, sizeof(m_uBits));
    pcBytes += sizeof(m_uBits);

    memcpy(&m_uNumBytes, pcBytes, sizeof(m_uNumBytes));
    pcBytes += sizeof(m_uNumBytes);

    memcpy(&m_uNumChannels, pcBytes, sizeof(m_uNumChannels));
    pcBytes += sizeof(m_uNumChannels);

    // Reserving space for vector
    auto uTimeChunksSize = m_uNumChannels*m_dChunkSize*m_uNumBytes;
    m_vvi16TimeChunks.resize(m_uNumChannels);

    for (unsigned uChannelIndex = 0; uChannelIndex < m_uNumChannels; ++uChannelIndex) 
        m_vvi16TimeChunks[uChannelIndex].resize(m_dChunkSize);

    // Filling data vector
    unsigned uSampleSize = sizeof(m_vvi16TimeChunks[0][0]);
    for (unsigned uChannelIndex = 0; uChannelIndex < m_uNumChannels; ++uChannelIndex) {
        for (unsigned uSampleIndex = 0; uSampleIndex < m_dChunkSize; uSampleIndex++)
        {
            memcpy(&m_vvi16TimeChunks[uChannelIndex][uSampleIndex], pcBytes, uSampleSize);
            pcBytes += uSampleSize;
        }
    }
}


