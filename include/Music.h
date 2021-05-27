#pragma once
#include <SFML/Audio.hpp>

class Music
{
public:
	virtual ~Music() = default; // close music file
	static Music& instance();

private:
	Music(); // open music file
	sf::Music m_music;
	sf::Music m_win;
};
