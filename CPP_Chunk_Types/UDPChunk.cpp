#include "UDPChunk.h"

UDPChunk::UDPChunk(unsigned m_uChunkLength) : BaseChunk(),
												m_uChunkLength(m_uChunkLength),
												m_vcDataChunk()
{
	m_vcDataChunk.resize(m_uChunkLength);
}

UDPChunk::UDPChunk(std::shared_ptr<UDPChunk> pUDPChunk): BaseChunk(pUDPChunk)
{
	m_uChunkLength = pUDPChunk->m_uChunkLength;
	m_vcDataChunk = pUDPChunk->m_vcDataChunk;
}