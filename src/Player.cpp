#include "Player.h"

Player::Player():ControlPlanet(sf::Color::Blue)
{
}

std::pair<bool,int> Player::controlled() const
{
	return m_controlled;
}

void Player::setControlled(bool c , int i)
{
	m_controlled.first = c;
	m_controlled.second = i;
}



