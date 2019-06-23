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

//DEFINES
#define RxD 0
#define TxD 1

//GLOBALS
SoftwareSerial BT(RxD, TxD);
LiquidCrystal_I2C lcd(0x27, 20, 4);
MENU menu;
SerialCommunication SC;

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
	//if (Serial3.available()) {
	//	char x = Serial3.read();
	//	Serial.write(x);
	//	lcd.print(x);		
	//}

	// MENU //
	menu.Print_Page(0);
	lcd.setCursor(8, 0);
	lcd.blink();
}

//char incomingByte =0;
int incomingMsg = 0;
long Header = 0;
//bool flag = 0;
//-------------------------------------------------------------------------------------
void loop()
{
	char incomingByte = 0;
	bool flag = 0;
	if (Serial3.available()) { incomingByte = Serial3.read(); flag = 1; }
	echo(incomingByte, flag);
	getMaze(incomingByte, flag);

	delay(1);
}
//-------------------------------------------------------------------------------------
void getMaze(char incomingByte, bool flag) {

}
//-------------------------------------------------------------------------------------
void echo(char incomingByte, bool flag) {
	//usb read
	if (Serial.available()) {
		//incomingByte = Serial.read();
		Serial.write(incomingByte);
		Serial3.write(incomingByte);
		lcd.print(incomingByte);
	}
	//bluetooth read
	if (flag) {
		//incomingByte = Serial3.read();
		lcd.print(incomingByte);
		Serial.print("(string)incomingByte:");
		Serial.println(incomingByte);
		//trap header
		incomingByte -= 48;
		if (incomingByte > 10) {incomingByte-=7;}
		Serial.print("(Hex)incomingByte:");
		Serial.println(incomingByte, HEX);
		Header <<= 4;
		Serial.print("(shifted)Header:");
		Serial.println(Header, HEX);
		Header = Header | (incomingByte & 0x0000000F);
		Serial.print("(or'ed)Header:");
		Serial.println(Header, HEX);
		Header &= 0x000000FF;
		Serial.print("(and'ed)Header:");
		Serial.println(Header, HEX);

		//Expect the new maze byte message 
		if (Header == HEADER_MAGIC) {
			lcd.print("fuckyesfuckyesfuckyes123");
		}

		//Serial3.write(x);
		Serial.print("\n");

	}
}
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