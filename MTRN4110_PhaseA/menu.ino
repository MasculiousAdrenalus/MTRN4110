


#include "menu.h"
#include "types.h"

MENU::MENU() {
	for (int i = 0; i < 5; i++) {
		this->thisBook.thisPage[i].pageN = i;
	}

	this->thisBook.thisPage[0].line1 = "Send AT:       ";
	this->thisBook.thisPage[0].line2 = "|  |  |  |";
	this->thisBook.thisPage[0].line3 = "|-- -- --|";
	this->thisBook.thisPage[0].line4 = "|  |  |  |";
	this->thisBook.thisPage[0].cursor.x = 8;
	this->thisBook.thisPage[0].cursor.y = 0;
	this->thisBook.thisPage[1].line1 = "Recieved maze:  ";
	this->thisBook.thisPage[1].line2 = "|        |";
	this->thisBook.thisPage[1].line3 = "|        |";
	this->thisBook.thisPage[1].line4 = "|        |";
	this->thisBook.thisPage[0].cursor.x = 12;
	this->thisBook.thisPage[0].cursor.y = 0;
}

MENU::~MENU() {}
coords MENU::Get_Cursor() { return thisBook.thisPage->cursor; };
int MENU::Get_PageN() { return this->currentPage; }

void MENU::Print_Page(int pageN) {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(this->thisBook.thisPage[pageN].line1);
	Serial.println(this->thisBook.thisPage[pageN].line1);
	lcd.setCursor(0, 1);
	lcd.print(this->thisBook.thisPage[pageN].line2);
	Serial.println(this->thisBook.thisPage[pageN].line2);
	lcd.setCursor(0, 2);
	lcd.print(this->thisBook.thisPage[pageN].line3);
	Serial.println(this->thisBook.thisPage[pageN].line3);
	lcd.setCursor(0, 3);
	lcd.print(this->thisBook.thisPage[pageN].line4);
	Serial.println(this->thisBook.thisPage[pageN].line4);
	
	this->prevPage = this->currentPage;
	this->currentPage = pageN;

	if (pageN == 0) {

	}
	Serial.print("\n");
}
void MENU::Print_Maze(packet pack) {
	switch (pack.command)
	{
	case 0:
		//decodes messages
		if (pack.dataH.index.b0 == 1) {
			lcd.print("a"); Serial.print("a");
		}
		if (pack.dataH.index.b1 == 1) {
			lcd.print("b"); Serial.print("b");
		}
		if (pack.dataH.index.b2 == 1) {
			lcd.print("c"); Serial.print("c");
		}
		if (pack.dataH.index.b3 == 1) {
			lcd.print("d"); Serial.print("d");
		}
		if (pack.dataH.index.b4 == 1) {
			lcd.print("e"); Serial.print("e");
		}
		if (pack.dataH.index.b5 == 1) {
			lcd.print("f"); Serial.print("f");
		}
		if (pack.dataH.index.b6 == 1) {
			lcd.print("g"); Serial.print("g");
		}
		if (pack.dataH.index.b6 == 1) {
			lcd.print("h"); Serial.print("h");
		}
		//
		if (pack.dataL.index.b0 == 1) {
			lcd.print("a"); Serial.print("a");
		}
		if (pack.dataL.index.b1 == 1) {
			lcd.print("b"); Serial.print("b");
		}
		if (pack.dataL.index.b2 == 1) {
			lcd.print("c"); Serial.print("c");
		}
		if (pack.dataL.index.b3 == 1) {
			lcd.print("d"); Serial.print("d");
		}
		if (pack.dataL.index.b4 == 1) {
			lcd.print("e"); Serial.print("e");
		}
		if (pack.dataL.index.b5 == 1) {
			lcd.print("f"); Serial.print("f");
		}
		if (pack.dataL.index.b6 == 1) {
			lcd.print("g"); Serial.print("g");
		}
		if (pack.dataL.index.b6 == 1) {
			lcd.print("h"); Serial.print("h");
		}
		break;
	}
}
