#include "StdAfx.h"
#include "SoundManager.h"


SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
	instanceFlag = false;
	for(std::map<std::string, sf::SoundBuffer*>::iterator i = m_soundBuffers.begin(); i != m_soundBuffers.end(); ++i)
	{
		m_soundBuffers.erase(i);
	}
	for(std::map<std::string, sf::Sound*>::iterator i = m_sounds.begin(); i != m_sounds.end(); ++i)
	{
		m_sounds.erase(i);
	}
}

bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::single = NULL;
SoundManager* SoundManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new SoundManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void SoundManager::Play(std::string soundName, float volume, bool variativePitch)
{
	m_sounds[soundName]->setVolume(volume);
	if(variativePitch)
	{
		m_sounds[soundName]->setPitch(0.9 + MathHelper::Random() * 0.1f);
	}
	else
	{
		m_sounds[soundName]->setPitch(1);
	}
	m_sounds[soundName]->play();
}


void SoundManager::Add(std::string soundName, std::string filePath, bool loop)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	buffer->loadFromFile(filePath);
	m_soundBuffers[soundName] = buffer;
	m_sounds[soundName] = new sf::Sound(*buffer);
	m_sounds[soundName]->setLoop(loop);
}