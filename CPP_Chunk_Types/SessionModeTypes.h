#ifndef Session_MODE_TYPES
#define Session_MODE_TYPES

/*
* List of Transport mode types.
* These intends to leverage the idea of the layer OSI model (layer 5)
* 
* This defines how data is packaged within the a UDP datagram or TCP data field
* and informs modules that follows UDP/TCP modules as to how to process the 
* data they have been passed
* 
* Data field descriptions are 
*/

enum class SessionModeTypes
{
	SM_SeqStateSize_1	//Session mode containing Sequence Number, Tx State, Size of data field.
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
struct SessionMode_1
{
	SessionModeTypes m_SessionModeType = SessionModeTypes::SM_SeqStateSize_1;
	unsigned m_uSequenceNumber = 0;
	char m_cTransmissionState = 4;
	unsigned m_uTransmissionSize = 5;
};
#endif