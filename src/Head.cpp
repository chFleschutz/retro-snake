#include "Head.h"

Head::Head(int width, int height, int maxBodys)
{
    m_borderX = width - 1;
    m_borderY = height - 1;
    m_posX = rand() % (width - 2) + 1 ;
    m_posY = rand() % (height - 2) + 1;
    m_maxBodys = maxBodys;

    m_body = new Body * [m_maxBodys];
    for (size_t i = 0; i < m_maxBodys; i++)
    {
        m_body[i] = nullptr;
    }
    m_body[0] = new Body(m_posX - 1, m_posY);
}

Head::~Head()
{
    for (size_t i = 0; i < m_maxBodys; i++)
    {
        delete m_body[i];
    }
    delete[] m_body;
}

//Hinzufügen eines neuen Körperteils zur Schlange
void Head::addBody()
{
    for (size_t i = 1;
        i < m_maxBodys;
        i++)
    {
        if (m_body[i] == nullptr)
        {
            m_body[i] = new Body(m_body[i - 1]->getPosX(), m_body[i - 1]->getPosY());
            break;
        }
    }
}

//Die Körperteile 1 weiterbewegen
void Head::moveBody()
{
    //Die Körperteile von hinten zum jeweiligen vorderen bewegen
    for (int i = m_maxBodys - 1; i > 0; i--)
    {
        //Prüfen ob Körperteil vorhanden
        if (m_body[i] != nullptr)
        {
            //Körperteil nach vorne verschieben
            m_body[i]->setPosX(m_body[i - 1]->getPosX());
            m_body[i]->setPosY(m_body[i - 1]->getPosY());
        }
    }
    //erstes Körperteil an die stelle des kopfes bewegen
    m_body[0]->setPosX(m_posX);
    m_body[0]->setPosY(m_posY);

}

//Festlegen der X-Position vom Schlangenkopf
void Head::setPosX(int x)
{
    //Prüfen auf verlassen des Spielfeldes in x-Richtung
    if (x <= 0)
    {
        m_posX = m_borderX - 1;
    }
    else if (x >= m_borderX)
    {
        m_posX = 1;
    }
    else
    {
        m_posX = x;
    }
}

//Festlegen der Y-Position vom Schlangekopf
void Head::setPosY(int y)
{
    //Prüfen auf verlassen des Spielfeldes in y-Richtung
    if (y <= 0)
    {
        m_posY = m_borderY - 1;
    }
    else if (y >= m_borderY)
    {
        m_posY = 1;
    }
    else
    {
        m_posY = y;
    }
}

//Zurückgeben der X-Position
int Head::getPosX()
{
    return m_posX;
}

//Zurückgeben der Y-Position
int Head::getPosY()
{
    return m_posY;
}

//Zurückgeben der X-Position des Körperteils an "stelle"
int Head::getBodyPosX(int stelle)
{
    return m_body[stelle]->getPosX();
}

//Zurückgeben der Y-Position des Körperteils an "stelle"
int Head::getBodyPosY(int stelle)
{
    return m_body[stelle]->getPosY();
}

//Gibt die X-Position des letzten Körperteils zurück
int Head::getLastBodyPosX()
{
    for (int i = m_maxBodys - 1; i > 0; i--)
    {
        if (m_body[i] != nullptr)
        {
            return m_body[i]->getPosX();
        }
    }
}

//Gibt die Y-Position des letzten Körperteils zurück
int Head::getLastBodyPosY()
{
    for (int i = m_maxBodys - 1; i > 0; i--)
    {
        if (m_body[i] != nullptr)
        {
            return m_body[i]->getPosY();
        }
    }
}

//Prüfen ob Snake an bestimmter stelle ein Körperteil hat
bool Head::hasBody(int stelle)
{
    if (m_body[stelle] != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Auf Kollision mit sich selbst prüfen
bool Head::isCrashed()
{
    for (size_t i = 1; i < m_maxBodys; i++)
    {
        if (m_body[i] != nullptr)
        {
            if (m_posX == m_body[i]->getPosX() && m_posY == m_body[i]->getPosY())
            {
                //Gameover
                return true;
            }
        }
        else
        {
            return false;
        }
    } 
}