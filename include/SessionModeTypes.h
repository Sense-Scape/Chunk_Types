#ifndef Session_MODE_TYPES
#define Session_MODE_TYPES

#include <utility>
#include "UDPChunk.h"

/*
* List of Session mode types.
* These intends to leverage the idea of the layer OSI model (layer 5)
* 
* This defines how data is packaged within the a UDP datagram or TCP data field
* and informs modules that follows UDP/TCP modules as to how to process the 
* data they have been passed
* 
* Data field descriptions are stored as pairs.
* First - Position of starting starting byte
* Second - Value of the header parameter
* Type - The type stored in the pair is the type and therefore number of bytes to read
*/

enum class SessionModeTypes
{
	SM_BaseMode,
	TimeChunkSession		///< Session mode containing Sequence Number, Tx State, Size of data field. Used for teh WAV TX Sesion
};


/*
* Base Session type used as inheritance mechanisim for derived session type
*/
class SessionModeBase 
{
public:
	SessionModeTypes m_SessionModeType = SessionModeTypes::SM_BaseMode;

	SessionModeBase(SessionModeTypes ceSessionType) { m_SessionModeType = ceSessionType; };
	virtual ~SessionModeBase() {};

	virtual void ConvertBytesToStates(std::shared_ptr<BaseChunk> pBaseChunk) {};
};

/*
* Session Mode 1
*
* Ordered data layout where the number is the byte position in the and the type
* is the type being read.
*
* unsigned m_uSequenceNumber;
* char m_cTransmissionState;
* unsigned m_uTransmissionSize;
*
*/
class TimeChunkSessionMode : public SessionModeBase
{
public:
	std::pair<unsigned,unsigned> m_puSequenceNumber = std::make_pair(0,0);							///< Map of sequence number (byte position and value)
	std::pair<char, char> m_pcTransmissionState = std::make_pair(4, 0);								///< Map of transmission state (byte position and value)
	std::pair<unsigned, unsigned> m_puTransmissionSize = std::make_pair(5,0);						///< Map of transmission data size (byte position and value)
	std::pair<unsigned, unsigned> m_pu32uChunkType = std::make_pair(9, 0);							///< Map of transmission data size (unused ish)
	std::pair<unsigned, uint32_t> m_puSessionNumber = std::make_pair(13, 0);
	std::pair<unsigned, std::string> m_pusMacUID = std::make_pair(17, "");							///< Map of transmission data size (byte position and value)
	unsigned m_uPreviousSequenceNumber = 0;															///< Unsigned previosuly received sequence number
	unsigned m_uPreviousSessionNumber = 0;
	unsigned m_uDataStartPosition = 24;																///< Starting position of data bytes

	TimeChunkSessionMode() : SessionModeBase(SessionModeTypes::TimeChunkSession) {};

	/**
	* @brief converts array of bytes into session states
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
