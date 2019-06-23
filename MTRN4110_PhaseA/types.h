#pragma once
#pragma pack(1)


#ifndef TYPES_H_
#define TYPES_H_


// ----------------------------------------
// Shorthand data types
// ----------------------------------------
// These will be used throughout the whole
// program instead of regular data types
// ----------------------------------------

// Signed types
typedef char INT8;
typedef int INT16;
typedef long INT32;

// Unsigned types
typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;



// ----------------------------------------
// UINT8
// ----------------------------------------

typedef union {
	struct {
		unsigned char	b0 : 1,
			b1 : 1,
			b2 : 1,
			b3 : 1,
			b4 : 1,
			b5 : 1,
			b6 : 1,
			b7 : 1;
	} index;
	unsigned char full;
} TUINT8;

// ----------------------------------------
// TUINT16 & TINT16
// ----------------------------------------
// Unions to efficiently access hi and lo 
// parts of short integers
//	Members:
//		Variable.s = full 16-bit number
//		Variable.c.Hi = top 8-bits
//		Variable.c.Lo = bottom 8-bits
// ----------------------------------------
typedef union
{
	INT16 s;
	struct
	{
		INT8 Lo;
		INT8 Hi;
	} c;
} TINT16;
typedef union
{
	UINT16 s;
	struct
	{
		UINT8 Lo;
		UINT8 Hi;
	} c;
} TUINT16;

// ----------------------------------------
// TUINT16 & TINT16
// ----------------------------------------
// Unions to efficiently access hi and lo
// parts of long integers
//	Members:
//		Variable.l = full 32-bit number
//		Variable.s.Hi = top 16-bits
//		Variable.s.Lo = bottom 16-bits
//		Variable.c.UpperHi = bits <31:24>
//		Variable.c.UpperLo = bits <23:16>
//		Variable.c.LowerHi = bits <15:8>
//		Variable.c.LowerLo = bits <7:0>
// ----------------------------------------

typedef union
{
	UINT32 l;
	struct
	{
		UINT16 Lo;
		UINT16 Hi;
	} s;
	struct
	{
		UINT8 LowerLo;
		UINT8 LowerHi;
		UINT8 UpperLo;
		UINT8 UpperHi;
	} c;
} TUINT32;

// ----------------------------------------
// TUINT16 & TINT16
// ----------------------------------------
// Union to efficiently access individual bytes of a float
//	Members:
//		Variable.d = full 32-bit float
//		Variable.dParts.dHi.s = top 16-bits
//		Variable.dParts.dLo.s = bottom 16-bits
//		Variable.dParts.dHi.c.Hi = bits <31:24>
//		Variable.dParts.dHi.c.Lo = bits <23:16>
//		Variable.dParts.dLo.c.Hi = bits <15:8>
//		Variable.dParts.dLo.c.Lo = bits <7:0>
// ----------------------------------------
typedef union
{
	float d;
	struct
	{
		TUINT16 dLo;
		TUINT16 dHi;
	} dParts;
} TFloat;


//////////////////PACKET STRUCTURE//////////////////////////////////
//typedef struct Packet {
//	UINT8 length; // 1byte
//	UINT8 command; // 1byte
//} Pack;

typedef struct {
	long header = 0;
	int command;
	TUINT8 dataH, dataL;
}packet;

typedef struct DataPacket {
	long HEADER = 0x06efcdab; //generic header 4bytes
	//uint seqNum;
	//UINT8 length; // 1byte
	UINT8 command; // 1byte

	unsigned int data;	//this is where the data lays, see types.h for more information on syntax notation
	UINT8 checksum;
} DP;
typedef struct DataPacket_2 {
	//UINT8 length;
	long HEADER = 0x06efcdab;
	UINT8 command;
	unsigned int dataA; //4bytes
	unsigned int dataB;	//this is where the data lays, see types.h for more information on syntax notation
	UINT8 checksum;
} DP_2;
typedef struct DataPacket_3 {
	long HEADER = 0x06efcdab;
	UINT8 command;
	unsigned int dataA; //4bytes
	unsigned int dataB;	//this is where the data lays, see types.h for more information on syntax notation
	unsigned int dataC;
	UINT8 checksum;
} DP_3;
typedef struct DataPacket_4 {
	long HEADER = 0x06efcdab;
	UINT8 command;
	unsigned int dataA; //4bytes
	unsigned int dataB;	//this is where the data lays, see types.h for more information on syntax notation
	unsigned int dataC;
	unsigned int dataD;
	UINT8 checksum;
} DP_4;
typedef struct DataPacket_5 {
	long HEADER = 0x06efcdab;
	UINT8 command;
	unsigned int dataA; //4bytes
	unsigned int dataB;	//this is where the data lays, see types.h for more information on syntax notation
	unsigned int dataC;
	unsigned int dataD;
	unsigned int dataE;
	UINT8 checksum;
} DP_5;
typedef struct DataPacket_6 {
	long HEADER = 0x06efcdab;
	UINT8 command;
	unsigned int dataA; //4bytes
	unsigned int dataB;	//this is where the data lays, see types.h for more information on syntax notation
	unsigned int dataC;
	unsigned int dataD;
	unsigned int dataE;
	unsigned int dataF;
	UINT8 checksum;
} DP_6;

#endif /* TYPES_H_ */