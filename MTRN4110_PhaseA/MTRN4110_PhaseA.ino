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
long Header = 0;
//-------------------------------------------------------------------------------------
void loop()
{
	char incomingMsg = 0;
	bool flag = 0;

	if (Serial3.available()) { 
		incomingMsg = Serial3.read();
		lcd.print(incomingMsg);
		Serial.print(incomingMsg);
		flag = 1;	
		getMaze(incomingMsg);
	}
	//echos commands
	echo(incomingMsg, flag);


	//delay(1);
}
//-------------------------------------------------------------------------------------
void getMaze(char incomingMsg) {

	//Serial.print("(string)incomingByte:");
	//Serial.println(incomingMsg);
	char incomingByte = 0;
	incomingByte = incomingMsg - 48;
	if (incomingByte > 10) { incomingByte -= 7; }
	//Serial.print("(Hex)incomingByte:");
	//Serial.println(incomingByte, HEX);
	Header <<= 4;
	//Serial.print("(shifted)Header:");
	//Serial.println(Header, HEX);
	Header = Header | (incomingByte & 0x0000000F);
	//Serial.print("(or'ed)Header:");
	//Serial.println(Header, HEX);
	Header &= 0x000000FF;
	//Serial.print("(and'ed)Header:");
	//Serial.println(Header, HEX);

	//Expect the new maze byte message 
	if (Header == HEADER_MAGIC) {

		menu.Print_Page(1);
		lcd.setCursor(15, 0);
		int incomingMsg = Serial3.read();
		Serial.print("\n");
	}
	
}
//-------------------------------------------------------------------------------------
void echo(char incomingMsg, bool flag) {
	//usb read
	if (Serial.available()) {
		incomingMsg = Serial.read();
		Serial.write(incomingMsg);
		Serial3.print(incomingMsg);
		lcd.print(incomingMsg);
	}
	//bluetooth echo
	if (flag) {
		//incomingByte = Serial3.read();

		//Serial.print("\n");
		//menu.Print_Page(menu.Get_PageN());
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