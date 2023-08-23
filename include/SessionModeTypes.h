#ifndef SESSION_MODE_TYPES
#define SESSION_MODE_TYPES

#include <utility>
#include "UDPChunk.h"

/*
* List of Session mode types.
* These intends to leverage the idea of the layer OSI model (layer 5)
*
* This defines how data is packaged within the a UDP datagram or TCP data field
* and informs modules that follows UDP/TCP modules as to how to process the
* data they have been passed
*/

enum class SessionModeType
{
	SessionModeBase,
	ReliableSessionSessionMode,
};


/*
* Base Session type used as inheritance mechanisim for derived session type
*/
class SessionModeBase
{
public:

	/**
	* @brief SessionModeBase constructor
	*/
	SessionModeBase() { };

	/**
	* @brief SessionModeBase destructor
	*/
	virtual ~SessionModeBase() {};

	/**
	* @brief Converts array of bytes into session states
	* @param[in] pBaseChunk base chunk of containing UDP char bytes
	*/
	virtual void ConvertBytesToStates(std::shared_ptr<BaseChunk> pBaseChunk) {};

	virtual SessionModeType GetSessionType() { return SessionModeType::SessionModeBase; }

};

/*
* ReliableSessionSessionMode
*
* Ordered data layout where the number is the byte position in the and the type
* is the type being read.
*
* Mode Structure
* | Sequence Number | Transmission State | Transmission Size | Chunk Type | Session Number | Unique Identifer |
*
* Counting in order of significance
* | Sequence Number | Session Number | Transmission State |
* First check transmission state, increment session
* Once transmissions state toggles, increment sequence and reset session
*/
class ReliableSessionSessionMode : public SessionModeBase
{
public:
	std::pair<unsigned, unsigned> m_puSequenceNumber = std::make_pair(0, 0);						///< Map of sequence number (byte position and value)
	std::pair<char, char> m_pcTransmissionState = std::make_pair(4, 0);								///< Map of transmission state (byte position and value)
	std::pair<unsigned, unsigned> m_puTransmissionSize = std::make_pair(5, 0);						///< Map of transmission data size (byte position and value)
	std::pair<unsigned, unsigned> m_pu32uChunkType = std::make_pair(9, 0);							///< Map of contained chunk type (byte position and value)
	std::pair<unsigned, uint32_t> m_puSessionNumber = std::make_pair(13, 0);						//< Map of session number (byte position and value)
	std::pair<unsigned, std::vector<uint8_t>> m_pusUID = std::make_pair(17, std::vector<uint8_t>({ 0,0,0,0,0,0 }));///< Map of transmission data size (byte position and value)
	unsigned m_uPreviousSequenceNumber = 0;															///< Unsigned previosuly received sequence number
	unsigned m_uPreviousSessionNumber = 0;															///< Unsigned previosuly received session number
	unsigned m_uDataStartPosition = 24;																///< Starting position of data bytes

	/**
	* @brief Constructor for the session mode
	* @param[in] Enumnerated session type corresponding to sessionModeType
	*/
	ReliableSessionSessionMode() : SessionModeBase() {};

	/**
	* @brief get the session mode type of session mode
	* @return return the enumerated type of the session mode
	*/
	SessionModeType GetSessionType() override { return SessionModeType::ReliableSessionSessionMode; }

	/**
	* @brief Converts array of bytes into session states
	* @param[in] pBaseChunk base chunk of containing UDP char bytes
	*/
	void ConvertBytesToStates(std::shared_ptr<BaseChunk> pBaseChunk) override
	{
		auto pUDPChunk = std::static_pointer_cast<UDPChunk>(pBaseChunk);

		// Parse and update processing states
		m_puSequenceNumber.second = *(reinterpret_cast<unsigned*>(&pUDPChunk->m_vcDataChunk[m_puSequenceNumber.first]));
		m_puTransmissionSize.second = *(reinterpret_cast<unsigned*>(&pUDPChunk->m_vcDataChunk[m_puTransmissionSize.first]));
		m_pu32uChunkType.second = *(reinterpret_cast<unsigned*>(&pUDPChunk->m_vcDataChunk[m_pu32uChunkType.first]));
		m_pcTransmissionState.second = *(reinterpret_cast<uint8_t*>(&pUDPChunk->m_vcDataChunk[m_pcTransmissionState.first]));
		m_puSessionNumber.second = *(reinterpret_cast<uint32_t*>(&pUDPChunk->m_vcDataChunk[m_puSessionNumber.first]));

		// Check where the chunk came from
		for (unsigned uMACIndex = 0; uMACIndex < 6; uMACIndex++)
			m_pusUID.second[uMACIndex] = *(reinterpret_cast<uint8_t*>(&pUDPChunk->m_vcDataChunk[m_pusUID.first + uMACIndex]));
	}


	/**
	* @brief Returns if the two classes are equal
	* @return Reference to the class with which we want to compare
	*/
	bool IsEqual(ReliableSessionSessionMode& reliableSessionSessionMode)
	{
		bool bIsEqual = (
			(m_puSequenceNumber == reliableSessionSessionMode.m_puSequenceNumber) &&
			(m_pcTransmissionState == reliableSessionSessionMode.m_pcTransmissionState) &&
			(m_puTransmissionSize == reliableSessionSessionMode.m_puTransmissionSize) &&
			(m_pu32uChunkType == reliableSessionSessionMode.m_pu32uChunkType) &&
			(m_puSessionNumber == reliableSessionSessionMode.m_puSessionNumber) &&
			(m_pusUID == reliableSessionSessionMode.m_pusUID) &&
			(m_uPreviousSequenceNumber == reliableSessionSessionMode.m_uPreviousSequenceNumber) &&
			(m_uPreviousSessionNumber == reliableSessionSessionMode.m_uPreviousSessionNumber) &&
			(m_uDataStartPosition == reliableSessionSessionMode.m_uDataStartPosition)
			);

		return bIsEqual;
	}

	/**
	 * @brief Get the size of object in bytes
	 * @return Custom size of object in bytes
	 */
	unsigned GetSize()
	{
		unsigned uByteSize = 0;

		// Then this class
		uByteSize += sizeof(m_puSequenceNumber.second);
		uByteSize += sizeof(m_pcTransmissionState.second);
		uByteSize += sizeof(m_puTransmissionSize.second);
		uByteSize += sizeof(m_pu32uChunkType.second);
		uByteSize += sizeof(m_puSessionNumber.second);
		uByteSize += sizeof(m_pusUID.second[0])*6;
		uByteSize += sizeof(m_uPreviousSequenceNumber);
		uByteSize += sizeof(m_uPreviousSessionNumber);

		return uByteSize;
	}

	/**
	 * @brief Fill a byte array the represents this object
	 * @return pByteArray Shared pointer to byte vector containing byte data
	 */
	std::shared_ptr<std::vector<char>> Serialise()
	{
		auto pvBytes = std::make_shared<std::vector<char>>();
		unsigned uSize = GetSize();
		pvBytes->reserve(uSize);
		char* pcBytes = pvBytes->data();

		memcpy(pcBytes, &m_puSequenceNumber.second, sizeof(m_puSequenceNumber.second));
		pcBytes += sizeof(m_puSequenceNumber.second);

		memcpy(pcBytes, &m_pcTransmissionState.second, sizeof(m_pcTransmissionState.second));
		pcBytes += sizeof(m_pcTransmissionState.second);

		memcpy(pcBytes, &m_puTransmissionSize.second, sizeof(m_puTransmissionSize.second));
		pcBytes += sizeof(m_puTransmissionSize.second);

		memcpy(pcBytes, &m_pu32uChunkType.second, sizeof(m_pu32uChunkType.second));
		pcBytes += sizeof(m_pu32uChunkType.second);

		memcpy(pcBytes, &m_puSessionNumber.second, sizeof(m_puSessionNumber.second));
		pcBytes += sizeof(m_puSessionNumber.second);

		// Converting vector to bytes
		for (const auto& u8UIDElement : m_pusUID.second)
		{
			unsigned uChunkSizeBytes = sizeof(u8UIDElement);
			memcpy(pcBytes, &u8UIDElement, uChunkSizeBytes);
			pcBytes += uChunkSizeBytes;
		}

		memcpy(pcBytes, &m_uPreviousSequenceNumber, sizeof(m_uPreviousSequenceNumber));
		pcBytes += sizeof(m_uPreviousSequenceNumber);

		memcpy(pcBytes, &m_uPreviousSessionNumber, sizeof(m_uPreviousSessionNumber));
		pcBytes += sizeof(m_uPreviousSessionNumber);

		return pvBytes;
	}

	/**
	 * @brief Converts byte array to object members
	 * @param[in] pvBytes Shared pointer to byte array that shall be used to construct memeber variables
	 */
	void Deserialise(std::shared_ptr<std::vector<char>> pvBytes)
	{
		char* pcBytes = pvBytes->data();

		// Converting members to bytes
		memcpy(&m_puSequenceNumber.second, pcBytes, sizeof(m_puSequenceNumber.second));
		pcBytes += sizeof(m_puSequenceNumber.second);

		memcpy(&m_pcTransmissionState.second, pcBytes, sizeof(m_pcTransmissionState.second));
		pcBytes += sizeof(m_pcTransmissionState.second);

		memcpy(&m_puTransmissionSize.second, pcBytes, sizeof(m_puTransmissionSize.second));
		pcBytes += sizeof(m_puTransmissionSize.second);

		memcpy(&m_pu32uChunkType.second, pcBytes, sizeof(m_pu32uChunkType.second));
		pcBytes += sizeof(m_pu32uChunkType.second);

		memcpy(&m_puSessionNumber.second, pcBytes, sizeof(m_puSessionNumber.second));
		pcBytes += sizeof(m_puSessionNumber.second);

		auto uSampleSize = sizeof(m_pusUID.second[0]);
		for (unsigned uUIDIndex = 0; uUIDIndex < 6; uUIDIndex++)
		{
			memcpy(&m_pusUID.second[uUIDIndex], pcBytes, uSampleSize);
			pcBytes += uSampleSize;
		}

		memcpy(&m_uPreviousSequenceNumber, pcBytes, sizeof(m_uPreviousSequenceNumber));
		pcBytes += sizeof(m_uPreviousSequenceNumber);

		memcpy(&m_uPreviousSessionNumber, pcBytes, sizeof(m_uPreviousSessionNumber));
		pcBytes += sizeof(m_uPreviousSessionNumber);
	}
};

#endif
