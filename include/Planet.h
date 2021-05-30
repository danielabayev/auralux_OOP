#pragma once
#include "Object.h"
#include "Unit.h"
#include <vector>
#include <memory>
//class Unit;

class Planet : public Object
{
public:
	Planet();
	~Planet();

private:
	sf::Sprite precentBar;
	int m_health;
	int m_unitToUpgrade;
	int m_currentLevel;
	int m_maxLevel;
	std::vector<std::shared_ptr<Unit>> m_units;
};