#pragma once
#include "Object.h"
//#include "Planet.h"
#include <utility>

class Unit : public Object
{
public:
    Unit() = default;
    virtual ~Unit() = default;
private:
	bool m_active = false;
	std::pair<int, int> m_target_position;
	//rotation/move
	//Planet* m_planet;
};
