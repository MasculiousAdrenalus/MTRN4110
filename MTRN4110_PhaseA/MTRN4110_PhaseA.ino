/*
    Name:       MTRN4110_PhaseA.ino
    Created:	22/06/2019 7:26:55 PM
    Author:     Bryce Gossling z3424655
*/
#pragma pack(1)


#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "menu.h"
#include "types.h"
#include "Hadware.h"
//DEFINES

//func defs

//GLOBALS
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
	//lcd.blink();
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