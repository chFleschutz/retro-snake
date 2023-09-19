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

//Zurückgeben der X-Position
int Food::getPosX()
{
	return m_posX;
}

//Zurückgeben der Y-Position
int Food::getPosY()
{
	return m_posY;
}