#pragma once
#include "Board.h"

class Controller
{//����� �� ���� ����, ����� ��� ������ �����
public:
	Controller(); // ctor
	virtual ~Controller() = default;
	void run();
private:
	Board m_board;
};