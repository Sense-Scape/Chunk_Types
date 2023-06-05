#include "BaseChunk.h"

BaseChunk::BaseChunk(std::vector<uint8_t> vu8SourceIdentifier) :
	m_vu8SourceIdentifier(vu8SourceIdentifier),
	m_u16SourceIndentifierSize(vu8SourceIdentifier.size())
{

}

BaseChunk::BaseChunk() :
	m_u16SourceIndentifierSize(0),
	m_vu8SourceIdentifier()
{

}

BaseChunk::BaseChunk(std::shared_ptr<BaseChunk> pBaseChunk)
{
	m_u16SourceIndentifierSize = pBaseChunk->m_u16SourceIndentifierSize;
	m_vu8SourceIdentifier = pBaseChunk->m_vu8SourceIdentifier;
}

BaseChunk::BaseChunk(const BaseChunk& baseChunk)
{
	m_u16SourceIndentifierSize = baseChunk.m_u16SourceIndentifierSize;
	m_vu8SourceIdentifier = baseChunk.m_vu8SourceIdentifier;
}

unsigned BaseChunk::GetSize()
{
	return GetInternalSize();
}

unsigned BaseChunk::GetInternalSize()
{
	unsigned uByteSize = 0;

	uByteSize += sizeof(m_u16SourceIndentifierSize);

	for (size_t stIndex = 0; stIndex < m_u16SourceIndentifierSize; stIndex++)
		uByteSize += sizeof(m_vu8SourceIdentifier[stIndex]);

	return uByteSize;
}

std::shared_ptr<std::vector<char>> BaseChunk::Serialise()
{
	auto pvBytes = std::make_shared<std::vector<char>>();
	pvBytes->resize(GetSize());
	char* pcBytes = pvBytes->data();

	// Converting members to bytes
	memcpy(pcBytes, &m_u16SourceIndentifierSize, sizeof(m_u16SourceIndentifierSize));
	pcBytes += sizeof(m_u16SourceIndentifierSize);

	// Converting vector to bytes
	if (m_vu8SourceIdentifier.size())
	{
		unsigned uChunkSizeBytes = sizeof(m_vu8SourceIdentifier[0]) * m_vu8SourceIdentifier.size();
		memcpy(pcBytes, &m_vu8SourceIdentifier[0], uChunkSizeBytes);
	}

	return pvBytes;
}

void BaseChunk::Deserialise(std::shared_ptr<std::vector<char>> pvBytes)
{
	char* pcBytes = pvBytes->data();

	// Converting members to bytes
	memcpy(&m_u16SourceIndentifierSize, pcBytes, sizeof(m_u16SourceIndentifierSize));
	pcBytes += sizeof(m_u16SourceIndentifierSize);

	// Lets get the meta data for the array
	m_vu8SourceIdentifier.resize(m_u16SourceIndentifierSize);
	unsigned uSampleSize = sizeof(m_vu8SourceIdentifier[0]);

	// If there is data in the vector
	if (m_vu8SourceIdentifier.size())
	{
		// Then lets now fill the vector
		for (unsigned uSampleIndex = 0; uSampleIndex < m_u16SourceIndentifierSize; uSampleIndex++)
		{
			memcpy(&m_vu8SourceIdentifier[uSampleIndex], pcBytes, uSampleSize);
			pcBytes += uSampleSize;
		}
	}
}

void BaseChunk::SetSourceIdentifier(std::vector<uint8_t> vu8SourceIdentifier)
{
	m_vu8SourceIdentifier = vu8SourceIdentifier;
	m_u16SourceIndentifierSize = vu8SourceIdentifier.size();
}

std::vector<uint8_t> BaseChunk::GetSourceIdentifier()
{
	return m_vu8SourceIdentifier;
}

bool BaseChunk::IsEqual(BaseChunk& baseChunk)
{	
	bool bIsEqual = (
		(m_u16SourceIndentifierSize == baseChunk.m_u16SourceIndentifierSize) &&
		(m_vu8SourceIdentifier == baseChunk.m_vu8SourceIdentifier)
		);

	return bIsEqual;
}