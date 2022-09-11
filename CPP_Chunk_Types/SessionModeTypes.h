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
	SM_SeqStateSize_1	//Session mode containing Sequence Number, Tx State, Size of data field.
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
class SessionMode_1 : public SessionModeBase
{
public:
	std::pair<unsigned,unsigned> m_puSequenceNumber = std::make_pair(0,0);
	std::pair<char, char> m_pcTransmissionState = std::make_pair(4, 0);;
	std::pair<unsigned, unsigned> m_puTransmissionSize = std::make_pair(5,0);;

	SessionMode_1() : SessionModeBase(SessionModeTypes::SM_SeqStateSize_1) {};
};
#endif