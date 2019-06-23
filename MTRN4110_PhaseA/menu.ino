


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
void MENU::Print_Maze(TUINT8 maze) {
		//decodes messages
		if (maze.index.b0 == 1) {
			//lcd.print("a"); Serial.print("a");
			lcd.setCursor(3, 1);
			lcd.print('|');
		}
		if (maze.index.b1 == 1) {
			//lcd.print("b"); Serial.print("b");
			lcd.setCursor(6, 1);
			lcd.print('|');
		}
		if (maze.index.b2 == 1) {
			//lcd.print("c"); Serial.print("c");
			lcd.setCursor(1, 2);
			lcd.print("--");
		}
		if (maze.index.b3 == 1) {
			//lcd.print("d"); Serial.print("d");
			lcd.setCursor(4, 2);
			lcd.print("--");
		}
		if (maze.index.b4 == 1) {
			//lcd.print("e"); Serial.print("e");
			lcd.setCursor(7, 2);
			lcd.print("--");
		}
		if (maze.index.b5 == 1) {
			//lcd.print("f"); Serial.print("f");
			lcd.setCursor(3, 3);
			lcd.print('|');
		}
		if (maze.index.b6 == 1) {
			//lcd.print("g"); Serial.print("g");
			lcd.setCursor(6, 3);
			lcd.print('|');
		}
		//not used
		//if (maze.index.b7 == 1) {
		//	//lcd.print("h"); Serial.print("h");
		//	//lcd.setCursor(8, 1);
		//	//lcd.print('|');
		//}
}
