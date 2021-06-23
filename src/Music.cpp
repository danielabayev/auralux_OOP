#include "Music.h"
//------------------------------------------------------------
Music::Music()
{
	m_BackgroundMusic.openFromFile("BackgroundMusic.wav");
	std::array <std::string, MUSICS> soundNames =
	{
		"MusicMenu", "ClickSound"
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
//------------------------------------------------------------
void Music::startMenuSound()
{
	m_sound[0].setBuffer(m_buffers[0]);
	m_sound[0].play();
}
////------------------------------------------------------------
//void Music::startBackgroundMusic()
//{
//	m_BackgroundMusic.play();
//	m_BackgroundMusic.setLoop(true);
//}
////------------------------------------------------------------
void Music::startClickSound()
{
	m_sound[1].setBuffer(m_buffers[1]);
	m_sound[1].play();
}
////------------------------------------------------------------
//void Music::startGameOverSound()
//{
//	m_sound[3].setBuffer(m_buffers[3]);
//	m_sound[3].play();
//}
////------------------------------------------------------------
//void Music::pauseBackgroundMusic()
//{
//	m_BackgroundMusic.pause();
//}
////------------------------------------------------------------
//void Music::pauseGameOverSound()
//{
//	m_sound[3].pause();
//}
