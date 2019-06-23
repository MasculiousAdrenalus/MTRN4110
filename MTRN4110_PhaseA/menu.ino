


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

	this->thisBook.thisPage[1].line1 = "Recieved maze:  ";
	this->thisBook.thisPage[1].line2 = "|        |";
	this->thisBook.thisPage[1].line3 = "|        |";
	this->thisBook.thisPage[1].line4 = "|        |";
}

MENU::~MENU() {}

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
}
void MENU::Print_Maze(char maze) {
	//TUINT8 newMaze = (TUINT8)maze;
}
