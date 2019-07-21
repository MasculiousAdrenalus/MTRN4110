#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

String str;
void setup() {
    Serial.begin(9600);
    Serial.write("Power On and ");
    delay(10);
      // LCD INIT //
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("test, world!");
}

void loop()
{
    while(!Serial.available());
    
    while (Serial.available() > 0) {
    //Serial.println("Arduino: ");
    //Serial.write(Serial.read());
    lcd.print(Serial.read());
//    Serial.flush();
    }
   
}
