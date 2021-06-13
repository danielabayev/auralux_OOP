#pragma once
#include "Board.h"
#include "Object.h"
#include "Planet.h"
#include "Screen.h"

class Controller
{//אחראי על השלב עצמו, עליית שלב וניהול המשחק
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run();
	Menuscreen menuScreen();
	int levelScreen();
private:
	sf::RenderWindow m_window;
	Board m_board;
	Screen m_screen;
	int m_level = 1;
};