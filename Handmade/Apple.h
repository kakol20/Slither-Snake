#pragma once
#include "GameObject.h"

#include "TextureManager.h"
#include "Sprite.h"
#include "Sphere.h"

#include <glm.hpp>
#include <math.h>
#include <iostream>

class Apple : public GameObject
{
public:
	Apple();
	virtual ~Apple();

	virtual void Update();
	virtual void Draw();
	virtual void Unload();

	Sphere GetBound() const;

private:
	Sprite m_texture;

	glm::vec2 m_size;
	glm::vec2 m_textureSize;

	std::string m_textureTag;

	Sphere m_bound;


};

