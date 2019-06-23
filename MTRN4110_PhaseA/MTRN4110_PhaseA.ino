/*
    Name:       MTRN4110_PhaseA.ino
    Created:	22/06/2019 7:26:55 PM
    Author:     Bryce Gossling z3424655
*/
#pragma pack(1)

#include "SerialCommunication.hpp"
#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "menu.h"
#include "types.h"
//DEFINES
#define RxD 0
#define TxD 1

char getHex(char ascii);
//GLOBALS


//-------------------------------------------------------------------------------------
class HC06 {
public:
	packet pack;
	char incomingMsg = 0;
	char incomingByte = 0;
	HC06();
	~HC06() {};
	void read();
	void getMaze();
	void echo();
};
HC06::HC06() {	

}
//-------------------------------------------------------------------------------------

//SoftwareSerial BT(RxD, TxD);
LiquidCrystal_I2C lcd(0x27, 20, 4);
MENU menu;
HC06 BT;

//-------------------------------------------------------------------------------------
void setup()
{
	// LCD INIT //
	lcd.init();
	lcd.backlight();
	lcd.clear();

	// SERIAL COMMUNICATIONS //
	// usb
	Serial.begin(115200);
	delay(500);
	Serial.println("Connection Started");
	// bluetooth
	Serial3.begin(115200);
	delay(500);
	Serial3.print("AT");

	// MENU //
	menu.Print_Page(0);
	lcd.setCursor(8, 0);
	lcd.blink();
}
//-------------------------------------------------------------------------------------
void loop()
{
	BT.read();

	//echos commands
	BT.echo();


	//delay(1);
}

//-------------------------------------------------------------------------------------
void HC06::read() {
	if (Serial3.available()) {
		this->incomingMsg = Serial3.read();
		lcd.print(incomingMsg);
		Serial.print(incomingMsg);
		getMaze();
	}
}
//-------------------------------------------------------------------------------------
void HC06::getMaze() {

	//Serial.print("(string)incomingByte:");
	//Serial.println(incomingMsg);
	incomingByte = getHex(incomingMsg);
	//incomingByte = incomingMsg - 48;
	//if (incomingByte > 10) { incomingByte -= 7; }
	//Serial.print("(Hex)incomingByte:");
	//Serial.println(incomingByte, HEX);
	pack.header <<= 4;
	//Serial.print("(shifted)Header:");
	//Serial.println(Header, HEX);
	pack.header = pack.header | (incomingByte & 0x0000000F);
	//Serial.print("(or'ed)Header:");
	//Serial.println(Header, HEX);
	pack.header &= 0x000000FF;
	//Serial.print("(and'ed)Header:");
	//Serial.println(Header, HEX);

	//Expect the new maze byte message 
	if (pack.header == HEADER_MAGIC) {
		menu.Print_Page(1);
		lcd.setCursor(15, 0);
		pack.command = getHex(Serial3.read());
		pack.dataH.full = getHex(Serial3.read());
		pack.dataL.full = getHex(Serial3.read());
		lcd.setCursor(0, 1);
		lcd.print("dataH:");
		lcd.print(pack.dataH.full);
		lcd.setCursor(0, 2);
		lcd.print("dataL:");
		lcd.print(pack.dataL.full);
		//option for different messages
		menu.Print_Maze(pack);
		
	}
	
}
//-------------------------------------------------------------------------------------
void HC06::echo() {
	//usb read
	if (Serial.available()) {
		incomingMsg = Serial.read();
		Serial.write(incomingMsg);
		Serial3.print(incomingMsg);
		lcd.print(incomingMsg);
	}
}
//-------------------------------------------------------------------------------------
char getHex(char ascii) {
	char hex = ascii - 48;
	if (hex > 10) { hex -= 7; }
	return hex;
}
//-------------------------------------------------------------------------------------


//uint32_t GetNumber()
//{
//	lcd.blink();
//	int count = 0;
//	uint32_t num = 0;
//	char key = customKeypad.getKey();
//	while (key != 'A')
//	{
//		if (count < 5) {
//			switch (key)
//			{
//			case NO_KEY: break;
//				//case '#': break; case '*': break;
//			case '0': case '1': case '2': case '3': case '4':
//			case '5': case '6': case '7': case '8': case '9':
//				lcd.print(key);
//				count++;
//				num = num * 10 + (key - '0');
//				break;
//			}
//
//		}
//		key = customKeypad.getKey();
//		if (key == 'B') return -1;
//	}
//	if (menu.currentPage == 6) {
//		all_motors[i].offset = num;
//		all_motors[i].get_offset();
//		lcd.setCursor(11, 0);
//		lcd.print("V:     uL");
//		lcd.setCursor(13, 0);
//		lcd.print((int)all_motors[i].volumeOffset);
//	}
//	lcd.noBlink();
//	return num;
//}