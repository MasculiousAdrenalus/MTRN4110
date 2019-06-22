

#pragma pack(1)
//#include <vector>
//#include <queue>
#include <Arduino.h>
#include "SerialCommunication.hpp"
//function constructors


SerialCommunication::SerialCommunication() {
	//	ack.length = 6;
	ack.command = 0xff;
	ack.HEADER = 0x06efcdab;//(unsigned int)0x06efdcab;
	//nack.length = 6;
	nack.command = 0xfe;
	nack.HEADER = 0x06efcdab;
}
SerialCommunication::~SerialCommunication() {}

void SerialCommunication::writeStruct(char *ptr, int structLength) {
	for (int i = 0; i < structLength; i++) {
		Serial.write(ptr[i]);
	}
}
void SerialCommunication::writeStruct() {
	char *ptr = (char*)&outPacket;
	for (int i = 0; i < sizeof(outPacket); i++) {
		Serial.write(ptr[i]);
	}
}
void SerialCommunication::writeACK() {
	char *ptr = (char*)&ack;
	for (int i = 0; i < 10; i++) {
		Serial.write(ptr[i]);
	}
}
void SerialCommunication::writeNACK() {
	char *ptr = (char*)&nack;
	for (int i = 0; i < 10; i++) {
		Serial.write(ptr[i]);
	}
}

void SerialCommunication::readSerial() {
	int incomingByte = 0;
	long Header = 0;
	DataPacket temp;
	//traps the header
	while (Serial.available() > 0) {
		do {
			incomingByte = Serial.read(); //Scheduler.delay(1);
			Header <<= 8;
			Header = Header | (incomingByte & 0x000000FF);
			Header &= 0x00FFFFFF;
		} while (Header != HEADER_MAGIC);
		//reads in packet length
		incomingByte = Serial.read(); //Scheduler.delay(1);
		length = incomingByte;
		char *ptr = (char *)malloc(length + 4);
		//reads rest of packet
		ptr[0] = 0xab;
		ptr[1] = 0xcd;
		ptr[2] = 0xef;
		ptr[3] = length;

		for (int i = 4; i < length + sizeof(Header); i++) {//for (int i = 0; i < (myPacket.length); i++) {
			incomingByte = Serial.read(); //Scheduler.delay(1);
			*(ptr + i) = (char)incomingByte; //ptr[i] = (char)incomingByte;
		}
		switch (length) {
		case DATAPACKET_SIZE:
			memcpy((unsigned char *)&(temp), ptr, sizeof(temp));
			//packets.push_back(temp); //remove this when checksum works
			checksum = CRC8(ptr, length + 3);
			break;
		case DATAPACKET_SIZE_2:
			memcpy((unsigned char *)&(myPacket_2)+1, ptr, sizeof(myPacket_2) - 1);
			break;
		case DATAPACKET_SIZE_3:
			memcpy((unsigned char *)&(myPacket_3)+1, ptr, sizeof(myPacket_3) - 1);
			break;
		case DATAPACKET_SIZE_4:
			memcpy((unsigned char *)&(myPacket_4)+1, ptr, sizeof(myPacket_4) - 1);
			break;
		case DATAPACKET_SIZE_5:
			memcpy((unsigned char *)&(myPacket_5)+1, ptr, sizeof(myPacket_5) - 1);
			break;
		case DATAPACKET_SIZE_6:
			memcpy((unsigned char *)&(myPacket_6)+1, ptr, sizeof(myPacket_6) - 1);
			break;
		}


		if (checksum == temp.checksum) {
			//send ack
			myPacket = temp;
			ack.data = temp.command;
			writeACK();
		}
		else {
			//sends a non acknowledge, meaning the data should be retransmitted
			nack.data = temp.command;
			writeNACK();
		}



		//enqueue(packets, myPacket);
		//length -= 1;
		//for (int i = 0; i < length; i++) {
		//	ptr[i] = ptr[i + 4];
		//}
		free(ptr);
	}

}

//DP SerialCommunication::getPacket() {
//	DP previous;
//	previous.command = NULL;
//	if (packets.size() >= 1) {
//		previous = packets.front();
//		packets.erase(packets.begin());
//		myPacket = packets.front();
//	}
//	return previous;
//}



//taken from http://www.devcoons.com/crc8/
char SerialCommunication::CRC8(const char *data, int length) {
	char crc = 0x00;
	char extract;
	char sum;
	for (int i = 0; i < length; i++)
	{
		extract = *data;
		for (char tempI = 8; tempI; tempI--)
		{
			sum = (crc ^ extract) & 0x01;
			crc >>= 1;
			if (sum)
				crc ^= 0x8C;
			extract >>= 1;
		}
		data++;
	}
	return crc;
}


//std::vector<DP>::iterator begin(std::vector<DP> elem) {
//	std::vector<DP>::iterator p = elem.begin();
//	return p;
//}
//DP peek(std::vector<DP> elem) {
//	return elem.front();
//}
//bool empty(std::vector<DP> elem) {
//	return elem.empty();
//}
//std::vector<DP>::iterator end(std::vector<DP> elem) {
//	std::vector<DP>::iterator p = elem.end();
//	return p;
//}
//
//void enqueue(std::vector<DP> elem, DP newElement) {
//	elem.push_back(newElement);
//}
//DP dequeue(std::vector<DP> elem) {
//	DP p = elem.front();
//	elem.erase(elem.begin());
//	return p;
//}

/*

		//sorts the packets based on their size
		switch (length) {
		case DATAPACKET_SIZE:
			memcpy((unsigned char *)&(temp), ptr, sizeof(temp));
			packets.push_back(temp); //remove this when checksum works
			//myPacket.length = length;
			checksum = CRC8(ptr, length + 3);

			if (checksum == temp.checksum) {

				//send ack
				myPacket = temp;
				ack.data = temp.command;
				writeACK();
			} else {
				//sends a non acknowledge, meaning the data should be retransmitted
				nack.data = temp.command;
				writeNACK();
			}
			break;
		case DATAPACKET_SIZE_2:
			memcpy((unsigned char *)&(myPacket_2)+1, ptr, sizeof(myPacket_2) - 1);
			myPacket_2.length = length;
			break;
		case DATAPACKET_SIZE_3:
			memcpy((unsigned char *)&(myPacket_3)+1, ptr, sizeof(myPacket_3) - 1);
			myPacket_3.length = length;
			break;
		case DATAPACKET_SIZE_4:
			memcpy((unsigned char *)&(myPacket_4)+1, ptr, sizeof(myPacket_4) - 1);
			myPacket_4.length = length;
			break;
		case DATAPACKET_SIZE_5:
			memcpy((unsigned char *)&(myPacket_5)+1, ptr,  sizeof(myPacket_5) - 1);
			myPacket_5.length = length;
			break;
		case DATAPACKET_SIZE_6:
			memcpy((unsigned char *)&(myPacket_6)+1, ptr, sizeof(myPacket_6) - 1);
			myPacket_6.length = length;
			break;
		}*/