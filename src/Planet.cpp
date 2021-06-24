#include "Planet.h"

Planet::Planet(sf::Color color, int maxLevel, sf::Vector2f pos, int index)
	:Object(color), m_unitToUpgrade(30), m_currentLevel(1), m_maxLevel(maxLevel),m_index(index),m_AmountToGenerate(4)
{

	m_circle.setRadius(SMALLPLANET);
	m_circle.setPosition(pos);
	m_circle.setOrigin(SMALLPLANET / 2, SMALLPLANET / 2);
	
	m_chargeColor = sf::Color::White;
	m_barScale = sf::Vector2f(0.95, 0.95);
	
	int pcolor = findColor(color);
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(pcolor));
	

}

void Planet::draw(sf::RenderWindow& window)
{
	window.draw(m_circle);
	if (m_charged)
		window.draw(m_upgrades);
	if (m_attacked)
		window.draw(m_healthBar);
	//window.draw(m_statusBar);
	//window.draw(m_fillBar);
	/*std::string hp = std::to_string(m_health);
	m_healthText.setString(hp);
	if(m_color == sf::Color::White)
		std::string st = "C" + std::to_string(m_counterToCharge);
	else
		std::string st = "U" + std::to_string(m_counterToUpgrade);
	window.draw(m_healthText);
	window.draw(m_chargeText)*/;
}



void Planet::setColor(sf::Color newColor)
{
	m_color = newColor;
	m_circle.setTexture(&Graphic::PicturesObject().getPlanet(findColor(newColor)));
}



void Planet::upgradePlanet()
{
	int size;
	if (m_circle.getRadius() == SMALLPLANET)
		size = MEDIUMPLANET;
	else
		size = LARGEPLANET;
	m_circle.setRadius(size);
	m_circle.setOrigin(size / 2, size / 2);
	m_currentLevel++;
	m_counterToUpgrade = 0;
	m_AmountToGenerate += 3;
	m_charged = false;
	m_barScale = sf::Vector2f(1.2, 1.2);

}

void Planet::setPosition(sf::Vector2f newPosition)
{
	m_circle.setPosition(newPosition);
}

sf::Vector2f Planet::getCenter()const
{
	return m_circle.getOrigin() + m_circle.getPosition();
}

float Planet::getRadius()const
{
	return m_circle.getRadius();
}

bool Planet::getActive() const
{
	return m_active;
}



void Planet::setActive(bool Active)
{
	m_active = Active;
}

int Planet::getHealth() const
{
	return m_health;
}

void Planet::setHealth(HealthAction action)
{
	if (action == INC)
		m_health++;
	else
	{
		m_health--;
	}

	setHealthStage();


	if (m_health == 0 || m_health == MAX_HEALTH)
	{
		m_attacked = false;
	}
	
		
}

int Planet::getCounterToUpgrade() const
{
	return m_counterToUpgrade;
}

void Planet::setCounterToUpgrade()
{
	m_counterToUpgrade++;
}



int Planet::getAmountToUpgrade() const
{
	return m_unitToUpgrade;
}

bool Planet::isMaxUpgrade() const
{
	return m_currentLevel == m_maxLevel;
}

void Planet::charge(sf::Color newCharger)
{
	if (m_chargeColor == sf::Color::White)
		m_chargeColor = newCharger;

	if (newCharger == m_chargeColor)
	{
		m_counterToCharge++;
		//Music::instance().startChargeSound();
	}
	else
	{
		if (m_counterToCharge != 0)
		{
			m_counterToCharge--;
		}
		else
		{
			m_chargeColor = newCharger;
			m_counterToCharge++;
			m_charged = false;
		}
	}
	UpgradeOptions status = getUpgrade(m_counterToCharge);
	setUpgradeStage(status, m_chargeColor);
	

	if (m_counterToCharge == m_unitToUpgrade)
	{
		setColor(m_chargeColor);
		setActive(true);
		m_counterToCharge = 0;
		m_charged = false;
		//for (auto& unit : m_units)
			//unit->setColor(m_chargeColor);
		//m_amountOfUnits = 0;
	}
}

void Planet::underAttack()
{
	setHealth(DEC);

	if (m_health == 0)
	{
		setActive(false);
		setColor(sf::Color::White);
		m_health = MAX_HEALTH;
		m_currentLevel = 1;
		m_counterToUpgrade = 0;
		m_counterToCharge = 0;
		m_amountOfUnits = 0;
		m_chargeColor = sf::Color::White;
		if (m_circle.getRadius() != SMALLPLANET)
		{
			m_circle.setRadius(SMALLPLANET);
			m_circle.setOrigin(SMALLPLANET / 2, SMALLPLANET / 2);
		}	
		m_AmountToGenerate = 4;
	}
}


void Planet::addToUpgrade()
{
	if (m_counterToUpgrade < m_unitToUpgrade)
	{

		m_counterToUpgrade++;
		//Music::instance().startChargeSound();
		
		UpgradeOptions status = getUpgrade(m_counterToUpgrade);
		setUpgradeStage(status, m_color);

		if (m_counterToUpgrade == m_unitToUpgrade)
			upgradePlanet();
	}
}

int Planet::getAmountOfUnits() const
{
	return m_amountOfUnits;
}

void Planet::addUnits(int i)
{
	m_amountOfUnits += i;
}
//-----------------------------------------------------
void Planet::decUnits()
{
	if (m_amountOfUnits != 0)
		m_amountOfUnits--;
	else
		throw "zero units";

}
int Planet::getIndex() const
{
		return m_index;
}
//-----------------------------------------------------
void Planet::resetUnits()
{
	m_amountOfUnits = 0;
}
//-----------------------------------------------------
void Planet::setUpgradeStage(UpgradeOptions stage, sf::Color color)
{
	switch (stage)
	{
	case UpgradeOptions::ONE:
		m_upgRect = sf::IntRect(0, 0, 120, 120);
		m_charged = true;
		break;
	case UpgradeOptions::TWO:
		m_upgRect = sf::IntRect(120, 0, 120, 120);
		break;
	case UpgradeOptions::THREE:
		m_upgRect = sf::IntRect(240, 0, 120, 120);
		break;
	case UpgradeOptions::FOUR:
		m_upgRect = sf::IntRect(360, 0, 120, 120);
		break;
	case  UpgradeOptions::FIVE:
		m_upgRect = sf::IntRect(480, 0, 120, 120);
		break;
	case UpgradeOptions::NONE:
		return;
	}
	m_upgrades = sf::Sprite(Graphic::PicturesObject().getUpgradeTexture(findColor(color)), m_upgRect);
	m_upgrades.setOrigin(60, 60);
	m_upgrades.setPosition(getCenter());
	m_upgrades.setScale(m_barScale);
}
//------------------------------------------------
UpgradeOptions Planet::getUpgrade(int upgradeAmount)
{
	switch (upgradeAmount)
	{
	case 6:
		return UpgradeOptions::ONE;
		break;
	case 12:
		return UpgradeOptions::TWO;
		break;
	case 18:
		return UpgradeOptions::THREE;
		break;
	case 24:
		return UpgradeOptions::FOUR;
		break;
	case 30:
		return UpgradeOptions::FIVE;
		break;
	default:
		return UpgradeOptions::NONE;
		break;
	}
}

void Planet::setHealthStage()
{
	switch (m_health)
	{
	case 20:
		m_healthRect = sf::IntRect(0, 0, 120, 120);
		
		break;
	case 40:
		m_healthRect = sf::IntRect(120, 0, 120, 120);
	
		break;
	case 60:
		m_healthRect = sf::IntRect(240, 0, 120, 120);
		
		break;
	case 80: 
		m_healthRect = sf::IntRect(360, 0, 120, 120);
		
		m_attacked = true;
		break;
	case 100:
		m_healthRect = sf::IntRect(480, 0, 120, 120);
		
		break;
	default:
		return;
	}
	m_healthBar = sf::Sprite((Graphic::PicturesObject().getHealthTexture()), m_healthRect);
	m_healthBar.setOrigin(60, 60);
	m_healthBar.setPosition(getCenter().x, getCenter().y);
	m_healthBar.setScale(0.65, 0.65);
}

int Planet::getAmountToGenerate() const
{
	return m_AmountToGenerate;
}
