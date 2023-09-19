#pragma once
#include <iostream>

class Food
{
public:
	Food(int width, int height);
	~Food();

	int getPosX();
	int getPosY();

private:
	int m_posX;
	int m_posY;

};

