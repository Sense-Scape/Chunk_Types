#include "UDPChunk.h"

UDPChunk::UDPChunk(unsigned m_uChunkLength) : BaseChunk(),
												m_uChunkLength(m_uChunkLength),
												m_vcDataChunk()
{
	m_vcDataChunk.resize(m_uChunkLength);
}