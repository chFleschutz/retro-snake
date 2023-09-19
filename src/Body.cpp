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

//R�ckgabe der X-Position des K�rperteils
int Body::getPosX()
{
	return m_posXBody;
}

//R�ckgabe der Y-Position des K�rperteils
int Body::getPosY()
{
	return m_posYBody;
}

//Festlegen der X-Position des K�rperteils
void Body::setPosX(int xPos)
{
	m_posXBody = xPos;
}

//Festlegen der Y-Position des K�rperteils
void Body::setPosY(int yPos)
{
	m_posYBody = yPos;
}
