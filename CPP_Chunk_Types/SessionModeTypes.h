#ifndef Session_MODE_TYPES
#define Session_MODE_TYPES

#include <utility>

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
	WAVSession		///< Session mode containing Sequence Number, Tx State, Size of data field. Used for teh WAV TX Sesion
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
class WAVSessionMode : public SessionModeBase
{
public:
	std::pair<unsigned,unsigned> m_puSequenceNumber = std::make_pair(0,0);		///< Map of sequence number (byte position and value)
	std::pair<char, char> m_pcTransmissionState = std::make_pair(4, 0);			///< Map of transmission state (byte position and value)
	std::pair<unsigned, unsigned> m_puTransmissionSize = std::make_pair(5,0);   ///< Map of transmission data size (byte position and value)
	unsigned m_uPreviousSequenceNumber = 0;										///< Unsigned previosuly received sequence number
	unsigned m_uDataStartPosition = 12;											///< Starting position of data bytes

	WAVSessionMode() : SessionModeBase(SessionModeTypes::WAVSession) {};
};
#endif