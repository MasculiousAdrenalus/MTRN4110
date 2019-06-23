#pragma once
#pragma pack(1)
#include "types.h"

typedef struct {
	int x, y;
}coords;
typedef struct PAGE {
	String line1;
	String line2;
	String line3;
	String line4;
	coords cursor;
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
	coords Get_Cursor();
	int Get_PageN();
	void Print_Page(int pageN);
	void Print_Maze(packet pack);

private:

};
