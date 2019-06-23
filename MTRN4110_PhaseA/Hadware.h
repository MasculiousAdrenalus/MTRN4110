// Hadware.h

#ifndef _HADWARE_h
#define _HADWARE_h
#include "types.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



class HC06 {
public:
	packet pack;
	TUINT8 maze;
	char incomingMsg = 0;
	char incomingByte = 0;
	HC06();
	~HC06() {};
	void read();
	void getMaze();
	void echo();
};
#endif

