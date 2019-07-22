#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

byte incomingByte = 0;

void setup() {
    Serial.begin(9600);
    Serial.write("Power On and ");
    delay(10);
    Serial3.begin(115200);
    Serial3.write("Power On and ");
    delay(10);
      // LCD INIT //
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("test, world!");
}

void loop()
{
//    while(!Serial.available());
    
    if (Serial.available() > 0) {
    //Serial.println("Arduino: ");
    //Serial.write(Serial.read());
    incomingByte = Serial.read();
    lcd.print(incomingByte);
//    Serial.flush();
    }
    if (Serial3.available() > 0) {
    //Serial.println("Arduino: ");
    //Serial.write(Serial.read());
    incomingByte = Serial3.read();
    Serial.println(incomingByte);
    lcd.print(incomingByte);
//    Serial.flush();
    }
   
}
