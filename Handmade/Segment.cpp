#include "Segment.h"

int Segment::s_totalSegments = 0;

Segment::Segment() // overload without a paramater
{
	if (s_totalSegments == 0)
	{
		TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/SnakeSegment.png", "SEGMENT");
	}

	// create a texture with random segment textures

	if (s_totalSegments == 0) // the first segment to be created is the head
	{
		m_tag = "SEGMENT_HEAD";

		m_position = glm::vec3(TheInput::Instance()->GetMousePosition(), 0.0f);

		m_layer = 0.0f;
	}
	else
	{
		m_tag = "SEGMENT_BODY";
		m_position = glm::vec3(0.0f);

		m_layer = 1.0f;
	}

	m_textureTag = "SEGMENT";
	m_texture.SetTexture("SEGMENT");

	m_size = glm::vec2(40.0f); // size of the segment
	m_textureSize = glm::vec2(500.0f); // size of the texture

	m_texture.SetSpriteDimension((int)m_size.x, (int)m_size.y);

	m_texture.SetTextureDimension(1, 1, (int)m_textureSize.x, (int)m_textureSize.y);

	m_speed = 8.0f;

	s_totalSegments++;

	m_isVisible = true;

	std::cout << "Segment created\n";
	std::cout << "---------------------------------------------------------------\n";
}

Segment::Segment(glm::vec3 position) // parameter of where the segment will spawn
{
	if (s_totalSegments == 0)
	{
		TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/SnakeSegment.png", "SEGMENT");
	}

	// create a texture with random segment textures

	if (s_totalSegments == 0)
	{
		m_tag = "SEGMENT_HEAD";

		m_position = glm::vec3(TheInput::Instance()->GetMousePosition(), 0.0f);
		
		m_layer = 0.0f;
	}
	else
	{
		m_tag = "SEGMENT_BODY";
		m_position = position;

		m_layer = 1.0f;
	}

	m_textureTag = "SEGMENT";
	m_texture.SetTexture("SEGMENT");

	m_size = glm::vec2(40.0f);
	m_textureSize = glm::vec2(500.0f);
	m_texture.SetSpriteDimension((int)m_size.x, (int)m_size.y);

	m_texture.SetTextureDimension(1, 1, 500, 500);

	m_speed = 8.0f;

	s_totalSegments++;

	m_isVisible = true;

	std::cout << "Segment created\n";
	//std::cout << "---------------------------------------------------------------" << std::endl;

}

Segment::~Segment()
{
	std::cout << "Segment destroyed\n";
	//std::cout << "---------------------------------------------------------------" << std::endl;

	s_totalSegments--;
}

void Segment::Update()
{
	// updating for collision
	m_bound.SetPosition((int)m_position.x, (int)m_position.y);
	m_bound.SetRadius(m_size.x / 2.0f);
}

void Segment::Draw()
{
	if (m_isVisible)
	{
		// have origin be in center instead of the top left
		float orginX = m_position.x - m_size.x / 2.0f;
		float orginY = m_position.y - m_size.y / 2.0f;

		m_texture.Draw((int)orginX, (int)orginY, (double)m_angle);
	}
}

void Segment::Unload()
{
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::CUSTOM_DATA, m_textureTag);
}

void Segment::Move(const glm::vec2 & position)
{
	glm::vec3 direction = glm::vec3(position, 0.0f) - m_position; // use inverse kinematics to move snake segments

	if (m_tag == "SEGMENT_HEAD") // the head will follow the mouse
	{
		if (glm::length(direction) > m_size.x) // the segment will be a certain distance away from the position it's following
		{
			direction = glm::normalize(direction) * m_speed;
			m_position = m_position + direction;
		}
		else
		{
			direction = glm::normalize(direction) * (m_size.x / 2.0f);
			m_position = glm::vec3(position, 0.0f) - direction;
		}
	}
	else
	{
		direction = glm::normalize(direction) * (m_size.x / 2.0f);
		m_position = glm::vec3(position, 0.0f) - direction;
	}

	m_angle = std::atan2(direction.y == 0.0f ? 0.01f : direction.y, direction.x == 0.0f ? 0.01f : direction.x); // rotate sprite to face the position it's following
	m_angle = glm::degrees(m_angle);
}

Sphere Segment::GetBound() const
{
	return m_bound;
}

glm::vec2 Segment::GetSize() const
{
	return m_size;
}

void Segment::SetSegmentCount(const int count)
{
	s_totalSegments = count;
}

void Segment::SetSpeed(const float speed)
{
	m_speed = speed;
}
