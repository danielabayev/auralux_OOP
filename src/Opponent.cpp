#include "Opponent.h"
#include <algorithm>

Opponent::Opponent(const sf::Color& color) :ControlPlanet(color),m_number_of_planets(m_mp.size())
{}

void Opponent::nextMove(const sf::Time& timePassed)
{
	if (m_mp.size() == 0)
		return;
	std::vector<std::vector<std::pair<bool, int>>> old_score;
	int old_number_planets;
	bool considerVeterans = false;
	if (m_number_of_planets <= m_mp.size())
	{
		old_score = m_planets_score;
		old_number_planets = m_number_of_planets; //in the reset score the number update
		considerVeterans = true;
	}

	resetScore();

	if (considerVeterans)
		veteransBonus(old_score, old_number_planets);

	makeMoves(timePassed);
}

void Opponent::makePlanetMove(ManagePlanet* p, int todo ,const sf::Time& timePassed)
{
	ManagePlanet* PlanetFrom;
	ManagePlanet* toConquer;
	switch (todo)
	{
	case HEAL:
		p->movePlayer(*p);
		return;
	case REINFORCMENT_TO:
		PlanetFrom = findNeighborReinforcment(p);
		if (PlanetFrom)
			return PlanetFrom->move(*p , timePassed);
		else
			if ((PlanetFrom = findProtectedPlanet()))
				return PlanetFrom->move(*p , timePassed);
		return;
	case CONQUER_NEW:
		toConquer = findConquer(p,sf::Color::White);
		p->move(*toConquer , timePassed);
		return;
	case CONQUER_CONQUER:
		toConquer = findConquer(p, p->getColor());
		p->move(*toConquer , timePassed);
		return;
	case UPGRADE:
		p->movePlayer(*p);
		return;
	case REINFORCMENT_FROM:
		PlanetFrom = findNeighborReinforcment(p);
		if (PlanetFrom)
			return p->move(*PlanetFrom , timePassed);
		else
			if (PlanetFrom = findProtectedPlanet())
				return p->move(*PlanetFrom , timePassed);
		return;
	}
}

void Opponent::resetScore()
{
	if (m_number_of_planets != m_mp.size())
	{//reset the size of the option vector
		m_planets_score.resize(m_mp.size());
		for (auto& scoreCol : m_planets_score)
		{
			scoreCol.resize(OPTIONS);
		}
		m_number_of_planets = m_mp.size();
	}

	//set true in the option needed
	for (int j = 0; j < m_mp.size(); j++)
	{
		int status = checkStatus(m_mp[j]);
		for (int i = 0; i < OPTIONS; i++)
			if (i == status)
			{
				m_planets_score[j][i].first = true;
				m_planets_score[j][i].second = getValue(m_mp[j], status);
			}
			else
			{
				m_planets_score[j][i].first = false;
				m_planets_score[j][i].second = 0;
			}
				
	}
}

int Opponent::checkStatus(const ManagePlanet* p)const
{
	///	6 priorities:
	/// 1 - heal 
	/// 2 - need reinforcment 
	/// 3 - conquer empty planet
	/// 4 - upgrade
	/// 5 - conquer near planet 
	/// 6 - send reinforcment 
	if (p->getPlanet().getHealth() < MAX_HEALTH)
	{
		int needToHeal = MAX_HEALTH - p->getPlanet().getHealth();
		if (needToHeal > p->getAmountOfUnits())
			return REINFORCMENT_TO;
		else
			return HEAL;
	}

	if (p->getAmountOfUnits() < START_UNIT_AMOUNT)
		return REINFORCMENT_TO;

	//need func of adjs
	for (auto& adj : p->getNeighbors())
		if (adj->getColor() == sf::Color::White)
			return CONQUER_NEW;

	if (!p->getPlanet().isMaxUpgrade())
		return UPGRADE;

	//need func of adjs
	for (auto& adj : p->getNeighbors())
		if (adj->getColor() != m_color)
			return CONQUER_CONQUER;

	return REINFORCMENT_FROM;
}

void Opponent::veteransBonus(const std::vector<std::vector<std::pair<bool, int>>>& old_score,const int old_planets)
{
	for (int i = 0; i < old_planets; i++)
		for (int j = 0; j < OPTIONS; j++)
		{
			if (old_score[i][j].first == m_planets_score[i][j].first)
				m_planets_score[i][j].second += 200;
		}
}

ManagePlanet* Opponent::findNeighborReinforcment(const ManagePlanet* p)const
{
	std::vector<ManagePlanet*> neig = p->getNeighbors();
	for (int i = 0; i < neig.size(); i++)
	{
		if (neig[i]->getAmountOfUnits() > START_UNIT_AMOUNT && neig[i]->getColor() == getColor())
			return neig[i];
	}
	return NULL;
}

ManagePlanet* Opponent::findProtectedPlanet()const
{
	for (int i = 0; i < m_mp.size(); i++)
	{
		std::vector<ManagePlanet*> neig = m_mp[i]->getNeighbors();
		int enemy = 0;
		for (int j = 0; j < neig.size(); j++)
		{
			if (neig[j]->getColor() != m_mp[i]->getColor())
				enemy++;
		}
		if (enemy <= 1)
			return m_mp[i];
	}
	return nullptr;
}

ManagePlanet* Opponent::findConquer(const ManagePlanet* p, const sf::Color& color)const
{
	std::vector<ManagePlanet*> neig = p->getNeighbors();
	std::vector<ManagePlanet*> toConquer;
	for (int i = 0; i < neig.size(); i++)
	{
		if (color == sf::Color::White)
		{
			if (neig[i]->getColor() == color)
				toConquer.push_back(neig[i]);
		}
		else {
			if (neig[i]->getColor() != color)
				toConquer.push_back(neig[i]);
		}
		
	}
	if (toConquer.size() == 0)
		throw "Incorrect function";
	int planet = rand();
	planet %= toConquer.size();
	return toConquer[planet];
}

int Opponent::getValue(const ManagePlanet* p, int status)const
{
	switch (status)
	{
	case HEAL:
		return getHealValue(p);
	case REINFORCMENT_TO:
		return getReinforcmentToValue(p);
	case CONQUER_NEW:
		return getConquerNewValue(p);
	case UPGRADE:
		return getUpgradeValue(p);
	case CONQUER_CONQUER:
		return getConquerConquerValue(p);
	case REINFORCMENT_FROM:
		return getReinforcmentFromValue(p);
	}
	//unknown value - dont get value
	return 0;
}

int Opponent::getHealValue(const ManagePlanet* p)const
{
	int value = 700;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getReinforcmentToValue(const ManagePlanet* p)const
{
	int value = 800;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getConquerNewValue(const ManagePlanet* p)const
{
	int value = 400;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getConquerConquerValue(const ManagePlanet* p)const
{
	int value = 150;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getUpgradeValue(const ManagePlanet* p)const
{
	int value = 300;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getReinforcmentFromValue(const ManagePlanet* p)const
{
	int value = 100;
	value += getNeighborValue(p);
	return value;
}

int Opponent::getNeighborValue(const ManagePlanet* p)const
{
	p->getPlanet();
	int value = 0;
	int friends = 0;
	int enemy = 0;

	for (auto& adj : p->getNeighbors())
		if (adj->getColor() != m_color)
		{
			value -= 50;
			enemy++;
		}
		else
			friends++;
	if (enemy == 0)
		enemy += 100;
	double relation = friends / enemy;
	if (relation > 1 )
		value += 100;
	if (relation < 0.5)
		value -= 50;

	return value;
}

void Opponent::makeMoves(const sf::Time& timePassed)
{
	int number_of_moves = m_mp.size() / 3;
	if (number_of_moves < 1)
		number_of_moves = 1;
	std::vector<std::pair<int, int>> indexes;
	for (int i = 0; i < m_mp.size(); i++)
		for (int j = 0; j < OPTIONS; j++)
			if (m_planets_score[i][j].first)
				indexes.push_back({ i,j });
	std::vector<std::pair<int, int>> values_of_indexes;
	int value;
	for (int i = 0; i < indexes.size(); i++)
	{
		value = m_planets_score[indexes[i].first][indexes[i].second].second;
		values_of_indexes.push_back({ i,value});
	}
	std::sort(values_of_indexes.begin(), 
			  values_of_indexes.end(), 
			  [](std::pair<int,int> a, std::pair<int, int> b) {return a.second > b.second;});
	while (number_of_moves != 0)
	{
		number_of_moves--;
		//first index indicate the planet number , seconed index indicate the option want to do
		std::pair<int,int> index = indexes[values_of_indexes[number_of_moves].first];
		makePlanetMove(m_mp[index.first],index.second , timePassed);
	}
}
