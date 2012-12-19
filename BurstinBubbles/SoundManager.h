#pragma once
#include <map>

class SoundManager
{
public:
	~SoundManager(void);
	static SoundManager* getInstance(void);
	void LoadTextures(void);
	std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
	std::map<std::string, sf::Sound*> m_sounds;
	void Play(std::string soundName, float volume = 100, bool variativePitch = false);
	void Add(std::string soundName, std::string filePath, bool loop = false);
private:
	static bool instanceFlag;
	static SoundManager *single;
	SoundManager(void);
};
