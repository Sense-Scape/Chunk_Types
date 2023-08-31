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
	char m_cTransmissionState;		///< Map of transmission state (byte position and value)
	uint32_t m_uSessionNumber;		///< Map of session number (byte position and value)
	uint32_t m_uSequenceNumber;		///< Map of sequence number (byte position and value)
	uint32_t m_u32uChunkType;		///< Map of contained chunk type (byte position and value)
	std::vector<uint8_t> m_usUID = std::vector<uint8_t>({ 0,0,0,0,0,0 });///< Map of unique unique identifier
	uint32_t m_uTransmissionSize;	///< Map of transmission data size (byte position and value, 0 - Transmitting; 1 - finished)

	/**
	* @brief Constructor for the session mode
	* @param[in] Enumnerated session type corresponding to sessionModeType
	*/
	ReliableSessionSessionMode() : SessionModeBase(),
		m_cTransmissionState(),
		m_uSessionNumber(),
		m_uSequenceNumber(),
		m_u32uChunkType(),
		m_uTransmissionSize()
	{
	};


	/**
	* @brief Copy constructor
	*/
	ReliableSessionSessionMode(ReliableSessionSessionMode& reliableSessionSessionMode)
	{
		m_cTransmissionState = reliableSessionSessionMode.m_cTransmissionState;
		m_uSessionNumber = reliableSessionSessionMode.m_uSessionNumber;
		m_uSequenceNumber = reliableSessionSessionMode.m_uSequenceNumber;
		m_u32uChunkType = reliableSessionSessionMode.m_u32uChunkType;
		m_usUID = reliableSessionSessionMode.m_usUID;
		m_uTransmissionSize = reliableSessionSessionMode.m_uTransmissionSize;
	}

	/**
	* @brief get the session mode type of session mode
	* @return return the enumerated type of the session mode
	*/
	SessionModeType GetSessionType() override { return SessionModeType::ReliableSessionSessionMode; }


	/**
	* @brief Returns if the two classes are equal
	* @return Reference to the class with which we want to compare
	*/
	bool IsEqual(ReliableSessionSessionMode& reliableSessionSessionMode)
	{
		bool bIsEqual = (
			(m_cTransmissionState == reliableSessionSessionMode.m_cTransmissionState) &&
			(m_uSessionNumber == reliableSessionSessionMode.m_uSessionNumber) &&
			(m_uSequenceNumber == reliableSessionSessionMode.m_uSequenceNumber) &&
			(m_u32uChunkType == reliableSessionSessionMode.m_u32uChunkType) &&
			(m_usUID == reliableSessionSessionMode.m_usUID) &&
			(m_uTransmissionSize == reliableSessionSessionMode.m_uTransmissionSize)
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
		uByteSize += sizeof(m_cTransmissionState);
		uByteSize += sizeof(m_uSessionNumber);
		uByteSize += sizeof(m_uSequenceNumber);
		uByteSize += sizeof(m_u32uChunkType);
		uByteSize += sizeof(m_usUID[0]) * 6;
		uByteSize += sizeof(m_uTransmissionSize);

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
		pvBytes->resize(uSize);
		char* pcBytes = pvBytes->data();

		memcpy(pcBytes, &m_cTransmissionState, sizeof(m_cTransmissionState));
		pcBytes += sizeof(m_cTransmissionState);

		memcpy(pcBytes, &m_uSessionNumber, sizeof(m_uSessionNumber));
		pcBytes += sizeof(m_uSessionNumber);

		memcpy(pcBytes, &m_uSequenceNumber, sizeof(m_uSequenceNumber));
		pcBytes += sizeof(m_uSequenceNumber);

		memcpy(pcBytes, &m_u32uChunkType, sizeof(m_u32uChunkType));
		pcBytes += sizeof(m_u32uChunkType);

		// Converting vector to bytes
		for (const auto& u8UIDElement : m_usUID)
		{
			unsigned uChunkSizeBytes = sizeof(u8UIDElement);
			memcpy(pcBytes, &u8UIDElement, uChunkSizeBytes);
			pcBytes += uChunkSizeBytes;
		}


		memcpy(pcBytes, &m_uTransmissionSize, sizeof(m_uTransmissionSize));
		pcBytes += sizeof(m_uTransmissionSize);

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
		memcpy(&m_cTransmissionState, pcBytes, sizeof(m_cTransmissionState));
		pcBytes += sizeof(m_cTransmissionState);

		memcpy(&m_uSessionNumber, pcBytes, sizeof(m_uSessionNumber));
		pcBytes += sizeof(m_uSessionNumber);

		memcpy(&m_uSequenceNumber, pcBytes, sizeof(m_uSequenceNumber));
		pcBytes += sizeof(m_uSequenceNumber);

		memcpy(&m_u32uChunkType, pcBytes, sizeof(m_u32uChunkType));
		pcBytes += sizeof(m_u32uChunkType);

		auto uSampleSize = sizeof(m_usUID[0]);
		for (unsigned uUIDIndex = 0; uUIDIndex < 6; uUIDIndex++)
		{
			memcpy(&m_usUID[uUIDIndex], pcBytes, uSampleSize);
			pcBytes += uSampleSize;
		}

		memcpy(&m_uTransmissionSize, pcBytes, sizeof(m_uTransmissionSize));
		pcBytes += sizeof(m_uTransmissionSize);
	}

	/**
	 * @brief increment session number
	 */
	void IncrementSession()
	{
		m_uSessionNumber++;
		m_uSequenceNumber = 0;

		// And reset transmission state
		m_cTransmissionState = 0;
	}

	/**
	 * @brief increment session number
	 */
	void IncrementSequence()
	{
		m_uSequenceNumber++;
	}
};

#endif
