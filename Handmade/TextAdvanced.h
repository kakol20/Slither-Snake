#pragma once

#include <string>
#include <algorithm>
#include <glm.hpp>

#include "TextureManager.h"
#include "Text.h"

class TextAdvanced
{
public:
	TextAdvanced();
	~TextAdvanced();

	void SetFontSize(int size);
	void SetPosition(float x, float y);
	void SetText(const std::string & text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetFont(const std::string & fontIndex);

	void Draw();

private:
	Text m_text;

	int m_fontSize;

	std::string m_string;

	glm::vec2 m_position;
};

