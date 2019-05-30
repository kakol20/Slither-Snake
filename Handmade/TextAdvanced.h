#pragma once

#include <string>
#include <algorithm>
#include <glm.hpp>

#include "TextureManager.h"
#include "Text.h"

class TextAdvanced
{
public:
	enum Pivot { TOP_LEFT, TOP_RIGHT, TOP_MIDDLE, MIDDLE_LEFT, CENTER, MIDDLE_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM_MIDDLE };

public:
	TextAdvanced();
	~TextAdvanced();

	void SetFontSize(int size);
	void SetPosition(float x, float y);
	void SetText(const std::string & text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetFont(const std::string & fontIndex);
	void SetPivot(const Pivot pivot);

	int GetTextSize();
	float GetTextWidth();
	size_t GetTextLength();
	glm::vec2 GetPosition();

	void Draw();

private:
	Text m_text;

	int m_fontSize;

	std::string m_string;

	glm::vec2 m_position;

	Pivot m_pivot;
};

