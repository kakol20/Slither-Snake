#ifndef SEGMENT_H
#define SEGMENT_H

#include "GameObject.h"

#include "Sprite.h"
#include "TextureManager.h"
#include "InputManager.h"

#include "Sphere.h"

#include <glm.hpp>
#include <math.h>
#include <iostream>

class Segment : public GameObject
{
public:
	Segment();
	virtual ~Segment();

	virtual void Update();
	virtual void Draw();
	virtual void Unload();

	void Move(const glm::vec2 & position);

	Sphere GetBound() const;

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


#endif // !SEGMENT_H
