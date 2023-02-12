#include "WatchdogChunk.h"

WatchdogChunk::WatchdogChunk(std::vector<uint8_t> &vu8MACAddress):
    BaseChunk(),
    m_vu8MACAddress(vu8MACAddress)
{
}

WatchdogChunk::WatchdogChunk(std::shared_ptr<WatchdogChunk> pWatchdogChunk) 
{
    m_vu8MACAddress = pWatchdogChunk->m_vu8MACAddress;  
}

unsigned WatchdogChunk::GetSize() 
{
    unsigned uByteSize = 0;

    uByteSize += sizeof(m_vu8MACAddress[0])*m_vu8MACAddress.size();

    return uByteSize;
}

std::shared_ptr<std::vector<char>> WatchdogChunk::Serialise()
{
    auto pvBytes = std::make_shared<std::vector<char>>();
    pvBytes->resize(GetSize());
    char* pcBytes = pvBytes->data();

    // Converting members to bytes
    memcpy(pcBytes, &m_vu8MACAddress[0], sizeof(m_vu8MACAddress[0])*m_vu8MACAddress.size());
    
    return pvBytes;
}

void WatchdogChunk::Deserialise(std::shared_ptr<std::vector<char>> pvBytes)
{
    char* pcBytes = pvBytes->data();

    // Converting members to bytes
    // Assumed 6 bytes as a MAC address is 6 bytes ...
    m_vu8MACAddress.resize(6);
    memcpy(&m_vu8MACAddress[0], pcBytes, 6);

}