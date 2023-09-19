#include "Body.h"

//Konstruktor
Body::Body(int x, int y)
{
	m_posXBody = x;
	m_posYBody = y;
}

//Destruktor
Body::~Body()
{
}

//Rückgabe der X-Position des Körperteils
int Body::getPosX()
{
	return m_posXBody;
}

//Rückgabe der Y-Position des Körperteils
int Body::getPosY()
{
	return m_posYBody;
}

//Festlegen der X-Position des Körperteils
void Body::setPosX(int xPos)
{
	m_posXBody = xPos;
}

//Festlegen der Y-Position des Körperteils
void Body::setPosY(int yPos)
{
	m_posYBody = yPos;
}
