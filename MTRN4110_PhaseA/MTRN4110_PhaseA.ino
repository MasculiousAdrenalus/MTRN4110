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
	// SERIAL COMMUNICATIONS //
	// usb
	Serial.begin(115200);
	delay(500);
	Serial.println("Connection Started");
	// bluetooth
	Serial3.begin(115200);
	delay(500);
	Serial3.print("AT");
	// LCD INIT //
	lcd.init();
	lcd.backlight();
	lcd.clear();
	lcd.print("Test:");


}

//-------------------------------------------------------------------------------------
void loop()
{
	char x, y;
	
	if (Serial.available()) {
		y = Serial.read();

		Serial.write(y);
		Serial3.write(y);
		lcd.print(y);
	}
	if (Serial3.available()) {
		x = Serial3.read();

		Serial.write(x);
		Serial3.write(x);
		lcd.print(x);
	}
	//delay(2);
}