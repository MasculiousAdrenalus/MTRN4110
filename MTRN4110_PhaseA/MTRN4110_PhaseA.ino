// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       MTRN4110_PhaseA.ino
    Created:	22/06/2019 7:26:55 PM
    Author:     Bryce Gossling z3424655
*/

#pragma pack(1)

#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//GLOBALS
LiquidCrystal_I2C lcd(0x27, 20, 4);
//-------------------------------------------------------------------------------------
void setup()
{
	lcd.init();
	lcd.backlight();
	lcd.clear();
	lcd.print("Testing...");


}
//-------------------------------------------------------------------------------------
void loop()
{


}
