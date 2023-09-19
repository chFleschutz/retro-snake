#pragma once
#include <iostream>
#include "Body.h"

class Head
{
public:
	Head(int xBorder, int yBorder, int maxBodys);
	~Head();

	void addBody();
	void moveBody();
	void setPosX(int x);
	void setPosY(int y);
	int getPosX();
	int getPosY();
	int getBodyPosX(int stelle);
	int getBodyPosY(int stelle);
	int getLastBodyPosX();
	int getLastBodyPosY();
	bool hasBody(int stelle);
	bool isCrashed();

private:
	Body** m_body = nullptr;
	int m_maxBodys;
	int m_borderX;
	int m_borderY;
	int m_posX;
	int m_posY;
};