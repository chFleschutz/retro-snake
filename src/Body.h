#pragma once
class Body
{
public:
	Body(int x, int y);
	~Body();

	int getPosX();
	int getPosY();
	void setPosX(int xPos);
	void setPosY(int yPos);

private:
	int m_posXBody;
	int m_posYBody;
};

