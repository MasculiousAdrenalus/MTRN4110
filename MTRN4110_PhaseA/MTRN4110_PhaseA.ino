/*
    Name:       MTRN4110_PhaseA.ino
    Created:	22/06/2019 7:26:55 PM
    Author:     Bryce Gossling z3424655
*/

#pragma pack(1)

#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>


//DEFINES
#define RxD 0
#define TxD 1

//GLOBALS
SoftwareSerial BT(RxD, TxD);

LiquidCrystal_I2C lcd(0x27, 20, 4);
//-------------------------------------------------------------------------------------
void setup()
{
	// Serial Comms
	Serial.begin(115200);
	Serial.println("Connection Started");
	delay(500);
	BT.begin(115200);
	BT.print("AT");
	delay(500);
	// LCD INIT
	lcd.init();
	lcd.backlight();
	lcd.clear();
	lcd.print("Testing...123");


}
char x, y;
//-------------------------------------------------------------------------------------
void loop()
{
	if (BT.available()) {
		x = BT.read();

		Serial.print(x);
		BT.print(y);
		lcd.print(x);
	}
	if (Serial.available()) {
		y = Serial.read();

		Serial.print(y);
		BT.print(y);
		lcd.print(y);
	}
	//delay(2);
}