#pragma once


#include "GameObject.h"

#include "Audio.h"
#include "Sprite.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "ScreenManager.h"
#include "Tools.h"

#include <SDL.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

class Background : public GameObject
{
public:
	Background();
	virtual ~Background();

	//void Create();

	void Load(const std::string & file, const std::string & textureID, int width, int height);
	virtual void Update();
	virtual void Draw();
	virtual void Unload();

private:
	Audio m_audio;
	Sprite m_background;

	glm::vec2 m_size;

	std::string m_audioTag;
	std::string m_textureTag;

	void SetTexture(const std::string & tag);
	void SetSize(const int width, const int height);
	void SetAudio(const std::string & tag, Audio::AudioType audioType);

};

