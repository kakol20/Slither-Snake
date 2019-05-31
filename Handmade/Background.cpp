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

	std::fstream dataFile("Data/Game.ini", std::ios_base::in);
	std::map<std::string, std::string> data;

	while (!dataFile.eof())
	{
		std::vector<std::string> subStr;
		std::string lineStr;

		std::getline(dataFile, lineStr);
		ParseString(subStr, lineStr, "=");
		data[subStr[0]] = subStr[1];
	}
	dataFile.close();

	TheAudio::Instance()->LoadFromFile(data["BGM"], AudioManager::MUSIC_AUDIO, "BGM");

	float newWidth = (float)width;
	float newHeight = (float)height;

	if ((newWidth / 16.0f) * newHeight < newHeight)
	{
		newWidth = (newHeight / 9.0f) * newWidth;
	}

	if ((newHeight / 9.0f) * newWidth < newWidth)
	{
		newHeight = (newWidth / 16.0f) * newHeight;
	}

	//SetTag("BG");
	m_tag = textureID;
	SetTexture(textureID);
	SetSize(width, height);

	m_isActive = false;
	m_isVisible = true;
	m_isAlive = true;

	SetAudio("BGM", Audio::MUSIC_AUDIO);

	m_tag = textureID;

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
		glm::vec2 position = glm::vec2(TheScreen::Instance()->GetScreenSize().x, TheScreen::Instance()->GetScreenSize().y);
		position = position / 2.0f;
		glm::vec2 calculatedPos = m_size / 2.0f;
		calculatedPos = position - calculatedPos;
		m_background.Draw((int)calculatedPos.x, (int)calculatedPos.y);
	}
}

void Background::Unload()
{
	//TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, m_textureTag);

	//TheAudio::Instance()->UnloadFromMemory(AudioManager::MUSIC_AUDIO, AudioManager::CUSTOM_AUDIO, m_audioTag);
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


