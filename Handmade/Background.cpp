#include "Background.h"

Background::Background()
{
	m_size = glm::vec2(0.0f);
}

Background::~Background()
{
	std::cout << "Background destroyed\n";

	//std::cout << "---------------------------------------------------------------" << std::endl;
}

void Background::Load(const std::string & file, const std::string & textureID, int width, int height)
{
	TheTexture::Instance()->LoadTextureFromFile(file, textureID);
	TheAudio::Instance()->LoadFromFile("Assets/Audio/Hiding_Your_Reality.ogg", AudioManager::MUSIC_AUDIO, "BGM");

	//SetTag("BG");
	m_tag = "BG";
	SetTexture(textureID);
	SetSize(width, height);

	m_isActive = false;
	m_isVisible = true;
	m_isAlive = true;

	SetAudio("BGM", Audio::MUSIC_AUDIO);

	m_tag = "BACKGROUND";

	m_audio.Play(Audio::PLAY_ENDLESS);
}

void Background::Update()
{
	if (m_isActive)
	{
		// update
	}
}

void Background::Draw()
{
	if (m_isVisible)
	{
		m_background.Draw();
	}
}

void Background::Unload()
{
	//TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, m_textureTag);

	TheAudio::Instance()->UnloadFromMemory(AudioManager::MUSIC_AUDIO, AudioManager::CUSTOM_AUDIO, m_audioTag);
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, m_textureTag);

}

void Background::SetTexture(const std::string & tag)
{
	m_textureTag = tag;

	m_background.SetTexture(tag);
}

void Background::SetSize(const int width, const int height)
{
	m_size = glm::vec2((float)width, (float)height);

	m_background.SetSpriteDimension(width, height);
	m_background.SetTextureDimension(1, 1, width, height);
}

void Background::SetAudio(const std::string & tag, Audio::AudioType audioType)
{
	m_audioTag = tag;
	m_audio.SetAudio(tag, audioType);
}


