#pragma once
#include "Board.h"
#include "Object.h"
#include "Planet.h"

class Controller
{//����� �� ���� ����, ����� ��� ������ �����
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run();
private:
	Board m_board;
};