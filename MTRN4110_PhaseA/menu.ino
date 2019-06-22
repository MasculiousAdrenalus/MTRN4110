


#include "menu.h"

MENU::MENU() {
	for (int i = 0; i < 5; i++) {
		this->thisBook.thisPage[i].pageN = i;
	}

	this->thisBook.thisPage[0].line1 = "Recieved maze:";
	this->thisBook.thisPage[0].line2 = "|  |  |  |";
	this->thisBook.thisPage[0].line3 = "|-- -- --|";
	this->thisBook.thisPage[0].line4 = "|  |  |  |";
}

MENU::~MENU() {}

int MENU::Get_PageN() { return this->currentPage; }

void MENU::Print_Page(int pageN) {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(this->thisBook.thisPage[pageN].line1);
	lcd.setCursor(0, 1);
	lcd.print(this->thisBook.thisPage[pageN].line2);
	lcd.setCursor(0, 2);
	lcd.print(this->thisBook.thisPage[pageN].line3);
	lcd.setCursor(0, 3);
	lcd.print(this->thisBook.thisPage[pageN].line4);

	this->prevPage = this->currentPage;
	this->currentPage = pageN;
}

