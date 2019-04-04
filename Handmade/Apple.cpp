#include "Apple.h"

Apple::Apple()
{
	std::srand((unsigned)time(0));
	
	m_tag = "APPLE";
	m_textureTag = "APPLE";

	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Apple.png", m_textureTag);

	m_position = glm::vec3(-100.0f, -100.0f, -100.0f);
	m_layer = 2.0f;

	m_textureSize = glm::vec2(500.0f);

	m_isActive = false;
	m_isVisible = true;

	m_size = glm::vec2(40.0f);
	m_texture.SetTexture(m_textureTag);
	m_texture.SetTextureDimension(1, 1, 500, 500);
	m_texture.SetSpriteDimension((int)m_size.x, (int)m_size.y);

	std::cout << "Apple created\n";
	//std::cout << "---------------------------------------------------------------" << std::endl;
}


Apple::~Apple()
{
	std::cout << "Apple destroyed\n";
	//std::cout << "---------------------------------------------------------------" << std::endl;
}

void Apple::Update()
{
	if (!m_isActive)
	{
		float x = (rand() % (int)(TheScreen::Instance()->GetScreenSize().x - (m_size.x * 2))) + m_size.x;
		float y = (rand() % (int)(TheScreen::Instance()->GetScreenSize().y - (m_size.x * 2))) + m_size.x;

		m_position = glm::vec3(x, y, 0.0f);

		m_isActive = true;
	}

	m_bound.SetPosition((int)m_position.x, (int)m_position.y);
	m_bound.SetRadius(m_size.x / 2.0f);
}

void Apple::Draw()
{
	if (m_isVisible)
	{
		// have origin be in center
		float orginX = m_position.x - m_size.x / 2.0f;
		float orginY = m_position.y - m_size.y / 2.0f;

		m_texture.Draw((int)orginX, (int)orginY, (double)m_angle);
	}
}

void Apple::Unload()
{
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, m_textureTag);
}

Sphere Apple::GetBound() const
{
	return m_bound;
}
