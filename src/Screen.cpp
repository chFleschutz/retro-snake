#include <windows.h>

#include "Screen.h"

//Konstruktor
Screen::Screen(char* screen, int width, int height)
{
	//Konsolen Cursor deaktivieren
	ShowConsoleCursor(false);
	//übergeben des Screen-Array in die Klasse
	m_screen = screen;
	m_width = width;
	m_height = height;
}

//Destruktor
Screen::~Screen()
{
}

void Screen::initializeScreen()
{
	//Cursor and die Richtige stelle setzen
	setCursor(0, 0);

	//Denn Screen mit druckbaren Zeichen füllen
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++) {
			*(m_screen + j + (i * m_width)) = ' ';
		}
	}

	//Ränder ins Array speichern 
	for (int i = 0; i < m_width; i++)
	{
		*(m_screen + i) = '#';								//oberkante
		*(m_screen + i + m_width * (m_height - 1)) = '#';	//unterkante
	}
	for (int i = 0; i < m_height; i++)
	{
		*(m_screen + i * m_width + m_width - 1) = '#';		//rechtekante
		*(m_screen + i * m_width) = '#';						//linkekante
	}

	//Array das erste mal ausgeben
	system("cls");
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			std::cout << *(m_screen + j + (i * m_width)) << ' ';
		}
		std::cout << std::endl;
	}
}

//Symbol an Position X Y ändern
void Screen::set(char zeichen, int x, int y)
{
	//Textfarbe für jeweiliges zeichen ändern
	int color;
	switch (zeichen)
	{
	case '#':
		color = 10;
		break;
	default:
		color = 15;
		break;
	}
	//Cursor zur position des zu ändernden zeichen bewegen und dann ändern
	setCursor(x, y, color);
	std::cout << zeichen;
}

//Konsolen-Cursor zu einer bestimmten Position bewegen
void Screen::setCursor(short x, short y, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x * 2, y };									//x * 2 da jedes 2te feld mit leer gefüllt ist um quadrate zu erhalten
	SetConsoleCursorPosition(hConsole, pos);					//Cursor zur Position x y bewegen
	SetConsoleTextAttribute(hConsole, color);					//Farbe des Zeichens festlegen (default weiß)
}

//Konsolen Cursor verstecken (weniger flackern)
void Screen::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Screen::gameOver()
{
	setCursor(m_width / 2 - 3, m_height / 2 - 2, 10);
	std::cout << "GAME OVER";
}
