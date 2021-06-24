#pragma once
#include <SFML/Audio.hpp>
#include <array>
class Music
{
public:
	virtual ~Music() = default; // close music file
	static Music &instance();
	void startBackgroundMusic();
	void startCollideSound();
	void startMenuSound();
	void startUnitSound();
	void startChargeSound();
	void startWinSound();
	void startClickSound();
	void startLoseSound();
	//void startGameOverSound();
	void stopBackgroundMusic();
	void pauseMenuMusic();
private:
	const static auto MUSICS = 7;
	Music(); // open music file
	sf::Music m_BackgroundMusic;
	std::array <sf::SoundBuffer, MUSICS> m_buffers;
	std::array<sf::Sound, MUSICS> m_sound;
};