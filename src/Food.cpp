#include "Food.h"

//Konstruktor
Food::Food(int width, int height)
{
	m_posX = rand() % (width - 2) + 1;
	m_posY = rand() % (height - 2) + 1;
}

//Destruktor
Food::~Food()
{
}

//Zur�ckgeben der X-Position
int Food::getPosX()
{
	return m_posX;
}

//Zur�ckgeben der Y-Position
int Food::getPosY()
{
	return m_posY;
}