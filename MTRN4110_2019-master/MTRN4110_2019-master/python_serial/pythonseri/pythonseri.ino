#include <arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

byte incomingByte = 0;
long header = 0;

void print_maze();

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
typedef struct{
  byte a,b,c,d,e,f,g,h,i,j;
}bytes_10;
bytes_10 maze;
byte arr[11];
void loop()
{
  header = 0;
    
    if (Serial3.available() > 0) {
      do {
        incomingByte = Serial3.read();
        header << 4;
        header =  header | (incomingByte & 0x000000FF);
        header &= 0x000000FF;
      } while (header != 0x000000AB);
      if (header == 0x000000AB){
        Serial.print("header:");
        Serial.println(header, HEX);
        for (int i = 0; i< 11; i++ ){
          arr[i] = Serial3.read();
          Serial.print(i);
          Serial.print(':');
          Serial.println(arr[i],HEX);
          delay(2);
        }
        if (arr[0] == 1){
          maze.a=arr[1];
          maze.b=arr[2];
          maze.c=arr[3];
          maze.d=arr[4];
          maze.e=arr[5];
          maze.f=arr[6];
          maze.g=arr[7];
          maze.h=arr[8];
          maze.i=arr[9];
          maze.j=arr[10];
        }
        if (arr[0] == 3){
          Serial.println("print the maze!!!!!!!");
          print_maze();
        }

      }
    }
    
   
}
void print_maze(){
  Serial.println("- - - - - - - - - - ");
  Serial.print(" ");
  

}
