// SerialCommunication.h
#pragma pack(1)

#ifndef _SERIALCOMMUNICATION_hpp
#define _SERIALCOMMUNICATION_hpp
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "Wire.h"
#else
#include "WProgram.h"
#endif
//CODE HERE
#define HEADER_MAGIC 0x00ABCDEF
#define DATAPACKET_SIZE 6
#define DATAPACKET_SIZE_2 10
#define DATAPACKET_SIZE_3 14
#define DATAPACKET_SIZE_4 18
#define DATAPACKET_SIZE_5 22
#define DATAPACKET_SIZE_6 26
#define DATAPACKET_SIZE_7 30


//#include <vector>
//#include <queue>
#include "types.h"


class SerialCommunication {
private:
public:
	//char *ptr; // random amount, adjust later
	//unsigned char *ptr = &buf[];
	//Pack currPack;
	DP myPacket;
	DP outPacket;
	DP ack;
	DP nack;
	int length;
	DP_2 myPacket_2;
	DP_3 myPacket_3;
	DP_4 myPacket_4;
	DP_5 myPacket_5;
	DP_6 myPacket_6;
	int checksum;
	//CommandMsg msg;
	bool flag;
	//std::vector<DP> packets;
	SerialCommunication();
	~SerialCommunication();
	void writeStruct(char *ptr, int structLength);
	void writeStruct();
	void writeACK();
	void writeNACK();
	void readSerial();
	//DP getPacket();
	char CRC8(const char *data, int length);
};
#endif

