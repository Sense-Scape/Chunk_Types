#include "WAVChunk.h"

WAVChunk::WAVChunk() : BaseChunk(),
					m_sWAVHeader(),
					m_vdData()
{

}

WAVChunk::WAVChunk(std::shared_ptr<WAVChunk> pWAVChunk)
{
	m_sWAVHeader = pWAVChunk->m_sWAVHeader;
	m_vdData = pWAVChunk->m_vdData;
}

WAVHeader WAVChunk::BytesToWAVHeader(std::vector<char>& vcWAVHeader)
{
	WAVHeader sWAVHeader;

	// RIFF
	sWAVHeader.RIFF[0] =  *(reinterpret_cast<uint8_t*>(&vcWAVHeader[0]));
	sWAVHeader.RIFF[1] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[1]));
	sWAVHeader.RIFF[2] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[2]));
	sWAVHeader.RIFF[3] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[3]));
	// ChunkSize
	sWAVHeader.ChunkSize = *(reinterpret_cast<uint32_t*>(&vcWAVHeader[4]));
	// WAVE
	sWAVHeader.WAVE[0] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[8]));
	sWAVHeader.WAVE[1] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[9]));
	sWAVHeader.WAVE[2] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[10]));
	sWAVHeader.WAVE[3] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[11]));
	// fmt
	sWAVHeader.fmt[0] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[12]));
	sWAVHeader.fmt[1] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[13]));
	sWAVHeader.fmt[2] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[14]));
	sWAVHeader.fmt[3] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[15]));
	// Subchunk1Size
	sWAVHeader.Subchunk1Size = *(reinterpret_cast<uint32_t*>(&vcWAVHeader[16]));
	// AudioFormat 
	sWAVHeader.AudioFormat = *(reinterpret_cast<uint16_t*>(&vcWAVHeader[20]));
	// NumOfChan
	sWAVHeader.NumOfChan = *(reinterpret_cast<uint16_t*>(&vcWAVHeader[22]));
	// SamplePerSec
	sWAVHeader.SamplesPerSec = *(reinterpret_cast<uint32_t*>(&vcWAVHeader[24]));
	// bytesPerSec
	sWAVHeader.bytesPerSec = *(reinterpret_cast<uint32_t*>(&vcWAVHeader[28]));
	// blockAlign 
	sWAVHeader.blockAlign = *(reinterpret_cast<uint16_t*>(&vcWAVHeader[32]));
	// bitsPerSample
	sWAVHeader.bitsPerSample = *(reinterpret_cast<uint16_t*>(&vcWAVHeader[34]));
	// Subchunk2ID
	sWAVHeader.Subchunk2ID[0] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[36]));
	sWAVHeader.Subchunk2ID[1] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[37]));
	sWAVHeader.Subchunk2ID[2] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[38]));
	sWAVHeader.Subchunk2ID[3] = *(reinterpret_cast<uint8_t*>(&vcWAVHeader[39]));
	// Subchunk2Size;
	sWAVHeader.Subchunk2Size = *(reinterpret_cast<uint32_t*>(&vcWAVHeader[40]));

   return sWAVHeader;
}

std::shared_ptr<std::vector<char>> WAVChunk::WAVHeaderToBytes()
{
	auto pvcByteData = std::make_shared<std::vector<char>>();
	pvcByteData->resize(44);

	std::memcpy(&(*pvcByteData)[0], &m_sWAVHeader.RIFF, sizeof(m_sWAVHeader.RIFF));                    // 0-3
	std::memcpy(&(*pvcByteData)[4], &m_sWAVHeader.ChunkSize, sizeof(m_sWAVHeader.ChunkSize));          // 4-7
	std::memcpy(&(*pvcByteData)[8], &m_sWAVHeader.WAVE, sizeof(m_sWAVHeader.WAVE));                    // 8-11
	std::memcpy(&(*pvcByteData)[12], &m_sWAVHeader.fmt, sizeof(m_sWAVHeader.fmt));                     // 12-15
	std::memcpy(&(*pvcByteData)[16], &m_sWAVHeader.Subchunk1Size, sizeof(m_sWAVHeader.Subchunk1Size)); // 16-19
	std::memcpy(&(*pvcByteData)[20], &m_sWAVHeader.AudioFormat, sizeof(m_sWAVHeader.AudioFormat));     // 20-21
	std::memcpy(&(*pvcByteData)[22], &m_sWAVHeader.NumOfChan, sizeof(m_sWAVHeader.NumOfChan));         // 22-23
	std::memcpy(&(*pvcByteData)[24], &m_sWAVHeader.SamplesPerSec, sizeof(m_sWAVHeader.SamplesPerSec)); // 24-27
	std::memcpy(&(*pvcByteData)[28], &m_sWAVHeader.bytesPerSec, sizeof(m_sWAVHeader.bytesPerSec));     // 28-31
	std::memcpy(&(*pvcByteData)[32], &m_sWAVHeader.blockAlign, sizeof(m_sWAVHeader.blockAlign));       // 32-33
	std::memcpy(&(*pvcByteData)[34], &m_sWAVHeader.bitsPerSample, sizeof(m_sWAVHeader.bitsPerSample)); // 34-35
	std::memcpy(&(*pvcByteData)[36], &m_sWAVHeader.Subchunk2ID, sizeof(m_sWAVHeader.Subchunk2ID));     // 36-40
	std::memcpy(&(*pvcByteData)[40], &m_sWAVHeader.Subchunk2Size, sizeof(m_sWAVHeader.Subchunk2Size)); // 41-44

	return pvcByteData;
}

void WAVChunk::FormatWAVHeaderBytes(std::shared_ptr<std::vector<char>> pvcWAVHeaderBytes)
{
	// Converting the following sets of bytes to big endian
	std::reverse((*pvcWAVHeaderBytes)[0], (*pvcWAVHeaderBytes)[3]);		// RIFF
	std::reverse((*pvcWAVHeaderBytes)[4], (*pvcWAVHeaderBytes)[7]);		// fmt
	std::reverse((*pvcWAVHeaderBytes)[19], (*pvcWAVHeaderBytes)[19]);	// subChunk1
	std::reverse((*pvcWAVHeaderBytes)[36], (*pvcWAVHeaderBytes)[40]);	// subChunk2
}


void WAVChunk::UnpackWAVData(std::shared_ptr<std::vector<std::vector<double>>> pvvdUnpackedWAVData)
{
	// Resizing and reserving unpacked vector to increase speed
	pvvdUnpackedWAVData->resize(m_sWAVHeader.NumOfChan);
	for (unsigned uChannelIndex = 0; uChannelIndex < m_sWAVHeader.NumOfChan; uChannelIndex++)
		(*pvvdUnpackedWAVData)[uChannelIndex].reserve(m_sWAVHeader.Subchunk2Size/ m_sWAVHeader.NumOfChan);

	unsigned uChannelIndex = 0;

	// Unpacking data into individual channels
	for (unsigned uDataIndex = 0; uDataIndex < m_vdData.size(); uDataIndex++)
	{
		(*pvvdUnpackedWAVData)[uChannelIndex].emplace_back(m_vdData[uDataIndex]);
		if (uChannelIndex > m_sWAVHeader.NumOfChan )
			uChannelIndex = 0;
	}
}