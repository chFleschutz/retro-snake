#pragma once
#include <iostream>
#include <Windows.h>

class Screen
{
public:
	Screen(char* screen, int width, int height);
	~Screen();

	void initializeScreen();
	void set(char name, int x, int y);
	void setCursor(short x, short y, int color = 15);
	void ShowConsoleCursor(bool showFlag);
	void gameOver();


private:
	char* m_screen;
	int m_width;
	int m_height;
};
