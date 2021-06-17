#include "Opponent.h"

Opponent::Opponent(sf::Color color):ControlPlanet(color)
{}

void Opponent::nextMove()
{
	resetScore();
}

void Opponent::resetScore()
{
	//reset the size of the option vector
	m_planets_score.resize(m_mp.size());
	for (auto& scoreCol : m_planets_score)
	{
		scoreCol.resize(OPTIONS);
	}
	//set true in the option needed
	for (int j = 0; j < m_mp.size() ; j++)
	{
		int status = checkStatus(m_mp[j]);
		for (int i = 0; i < OPTIONS; i++)
			if (i == status)
				m_planets_score[j][i].first = true;
			else
				m_planets_score[j][i].first = false;
	}
}

int Opponent::checkStatus(ManagePlanet* p)
{
	///	6 priorities:
	/// 1 - heal
	/// 2 - need reinforcment
	/// 3 - conquer empty planet
	/// 4 - upgrade
	/// 5 - conquer near planet 
	/// 6 - send reinforcment
	/*if (p->needHeal())
		return HEAL;*/
	return 8;
}
