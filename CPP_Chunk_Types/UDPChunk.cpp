#include "UDPChunk.h"

UDPChunk::UDPChunk(unsigned m_uChunkLength) : BaseChunk(),
												m_uChunkLength(m_uChunkLength),
												m_cvDataChunk()
{
	m_cvDataChunk.resize(m_uChunkLength);
}