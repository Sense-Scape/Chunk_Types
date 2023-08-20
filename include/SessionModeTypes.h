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
	std::pair<unsigned, unsigned> m_puSequenceNumber = std::make_pair(0, 0);	///< Map of sequence number (byte position and value)
	std::pair<char, char> m_pcTransmissionState = std::make_pair(4, 0);			///< Map of transmission state (byte position and value)
	std::pair<unsigned, unsigned> m_puTransmissionSize = std::make_pair(5, 0);	///< Map of transmission data size (byte position and value)
	std::pair<unsigned, unsigned> m_pu32uChunkType = std::make_pair(9, 0);		///< Map of contained chunk type (byte position and value)
	std::pair<unsigned, uint32_t> m_puSessionNumber = std::make_pair(13, 0);	///< Map of session number (byte position and value)
	std::pair<unsigned, std::string> m_pusMacUID = std::make_pair(17, "");		///< Map of transmission data size (byte position and value)
	unsigned m_uPreviousSequenceNumber = 0;										///< Unsigned previosuly received sequence number
	unsigned m_uPreviousSessionNumber = 0;										///< Unsigned previosuly received session number
	unsigned m_uDataStartPosition = 24;											///< Starting position of data bytes

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
		m_pcTransmissionState.second = *(reinterpret_cast<uint8_t*>(&pUDPChunk->m_vcDataChunk[m_pcTransmissionState.first]));
		m_puSessionNumber.second = *(reinterpret_cast<uint32_t*>(&pUDPChunk->m_vcDataChunk[m_puSessionNumber.first]));

		// If the MAC address has been set, don't parse again
		if (m_pusMacUID.second == "")
		{
			// Parse and convert each byte to base 10 string to uniquely identify process
			for (unsigned uMACIndex = 0; uMACIndex < 6; uMACIndex++)
				if (uMACIndex != 5)
					m_pusMacUID.second += std::to_string(*(reinterpret_cast<uint8_t*>(&pUDPChunk->m_vcDataChunk[m_pusMacUID.first + uMACIndex]))) + ":";
				else
					m_pusMacUID.second += std::to_string(*(reinterpret_cast<uint8_t*>(&pUDPChunk->m_vcDataChunk[m_pusMacUID.first + uMACIndex])));
		}
	};
};

#endif

