#pragma once

#include "GameObject.h"

#include <glm.hpp>
#include <math.h>
#include <iostream>

#include "Sprite.h"
#include "TextureManager.h"
#include "InputManager.h"

#include "Sphere.h"

class Segment : public GameObject
{
public:
	Segment();
	Segment(glm::vec3 position);
	virtual ~Segment();

	virtual void Update();
	virtual void Draw();
	virtual void Unload();

	void Move(const glm::vec2 & position);

	Sphere GetBound() const;

	glm::vec2 GetSize() const;

	void SetSpeed(const float speed);

private:
	Sprite m_texture;

	glm::vec2 m_size;
	glm::vec2 m_textureSize;

	std::string m_textureTag;

	static int s_totalSegments;

	float m_speed;

	Sphere m_bound;
};
