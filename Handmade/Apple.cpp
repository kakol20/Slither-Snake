#include "Apple.h"



Apple::Apple()
{
	m_tag = "APPLE";
	m_textureTag = "APPLE";

	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Apple.png", m_textureTag);

	m_position = glm::vec3(-100.0f, -100.0f, -100.0f);
	m_layer = 2.0f;

	m_size = glm::vec2(20.0f);
	m_textureSize = glm::vec2(500.0f);


}


Apple::~Apple()
{
}

void Apple::Update()
{
}

void Apple::Draw()
{
}

void Apple::Unload()
{
}

Sphere Apple::GetBound() const
{
	return m_bound;
}
