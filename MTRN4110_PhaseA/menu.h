#pragma once
#include "types.h"

typedef struct PAGE {
	String line1;
	String line2;
	String line3;
	String line4;
	int pageN;
} page;

typedef struct BOOK {
	page thisPage[5];
} book;

class MENU {
public:
	book thisBook;
	int currentPage;
	int prevPage;
	MENU();
	~MENU();
	int Get_PageN();
	void Print_Page(int pageN);
	void Print_Maze(char maze);
private:

};
