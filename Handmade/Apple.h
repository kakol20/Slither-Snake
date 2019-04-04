#pragma once
#include "GameObject.h"

#include <glm.hpp>
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include <iostream>

#include "ScreenManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Sphere.h"


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

