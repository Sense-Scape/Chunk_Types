#include "TimeChunk.h"

TimeChunk::TimeChunk(double dChunkSize, double dSampleRate, double dTimeStamp, unsigned uBits, unsigned uNumBytes) : BaseChunk(),
m_dChunkSize(dChunkSize),
m_dSampleRate(dSampleRate),
m_dTimeStamp(dTimeStamp),
m_uBits(uBits),
m_uNumBytes(uNumBytes),
m_uNumChannels()
{
}

TimeChunk::TimeChunk(std::shared_ptr<TimeChunk> pTimeChunk)
{
    m_dChunkSize = pTimeChunk->m_dChunkSize;
    m_dSampleRate = pTimeChunk->m_dSampleRate;
    m_dTimeStamp = pTimeChunk->m_dTimeStamp;
    m_uBits = pTimeChunk->m_uBits;
    m_uNumBytes = pTimeChunk->m_uNumBytes;
    m_uNumChannels = pTimeChunk->m_uNumChannels;
    m_vvvdTimeChunk = pTimeChunk->m_vvvdTimeChunk;
}

TimeChunk::TimeChunk(const TimeChunk& timeChunk) : BaseChunk()
{
    m_vvvdTimeChunk = timeChunk.m_vvvdTimeChunk;
    m_uBits = timeChunk.m_uBits;
    m_uNumChannels = timeChunk.m_uNumChannels;
}