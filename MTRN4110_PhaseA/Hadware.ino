// 
// 
// 

#include "Hadware.h"
#include "types.h"

char getHex(char ascii) {
	char hex = ascii - 48;
	if (hex > 10) { hex -= 7; }
	return hex;
}

//-------------------------------------------------------------------------------------
HC06::HC06() {

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
	if (pack.header == 0x000000AB) {
		menu.Print_Page(1);
		lcd.setCursor(15, 0);
		pack.command = getHex(Serial3.read());
		pack.dataH.full = getHex(Serial3.read());
		pack.dataL.full = getHex(Serial3.read());
		//lcd.print("data result:");
		maze.full = pack.dataH.full * 10 + pack.dataL.full;
		lcd.print(maze.full);
		//option for different messages
		switch (pack.command)
		{
		case 0:
			menu.Print_Maze(maze);
			break;
		}

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