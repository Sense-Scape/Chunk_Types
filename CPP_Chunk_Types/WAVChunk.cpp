#include "WAVChunk.h"

WAVChunk::WAVChunk() : BaseChunk(),
					m_sWAVHeader(),
					m_vdData()
{

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
		if (uChannelIndex >= m_sWAVHeader.NumOfChan - 1)
			uChannelIndex = 0;
	}
}