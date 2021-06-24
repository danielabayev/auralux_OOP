#include "Music.h"
//------------------------------------------------------------
Music::Music()
{
	m_BackgroundMusic.openFromFile("MusicBackground.wav");
	std::array <std::string, MUSICS> soundNames =
	{
		"MusicMenu", "ClickSound", "charge", "Upgrade"
	};

	for (int i = 0; i < soundNames.size(); i++)
	{
		m_buffers[i].loadFromFile(soundNames[i] + ".wav");
	}
}
//------------------------------------------------------------
Music& Music::instance()
{
	static Music music;
	return music;
}
//---------------------------------------------------------
void Music::startBackgroundMusic()
{
	m_BackgroundMusic.setVolume(50.f);
	m_BackgroundMusic.play();
	m_BackgroundMusic.setLoop(true);
}
//------------------------------------------------------------
void Music::startMenuSound()
{
	m_sound[0].setVolume(10.f);
	m_sound[0].setBuffer(m_buffers[0]);
	m_sound[0].play();
}
//------------------------------------------------------
void Music::startClickSound()
{
	m_sound[1].setVolume(10.f);
	m_sound[1].setBuffer(m_buffers[1]);
	m_sound[1].play();
}
//------------------------------------------------------------
void Music::startUnitSound()
{
	m_sound[1].setVolume(70.f);
	m_sound[2].setBuffer(m_buffers[2]);
	m_sound[2].play();
}
//------------------------------------------------------------
void Music::startChargeSound()
{
	m_sound[1].setVolume(70.f);
	m_sound[3].setBuffer(m_buffers[3]);
	m_sound[3].play();
}
//------------------------------------------------------------
void Music::stopBackgroundMusic()
{
	m_BackgroundMusic.pause();
}
//-------------------------------------------------------
void Music::pauseMenuMusic()
{
	m_sound[0].pause();
}
