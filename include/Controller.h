#pragma once
#include "Board.h"

class Controller
{//אחראי על השלב עצמו, עליית שלב וניהול המשחק
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run();
private:
	Board m_board;
};