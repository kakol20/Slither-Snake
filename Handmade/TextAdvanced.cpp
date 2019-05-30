#include "TextAdvanced.h"



TextAdvanced::TextAdvanced()
{
	m_fontSize = 50;
	m_string = "N/A";
	m_pivot = TOP_LEFT;
}


TextAdvanced::~TextAdvanced()
{
}

void TextAdvanced::SetFontSize(int size)
{
	m_fontSize = size;

	m_text.SetSize(m_string.size() * (m_fontSize / 2), m_fontSize);
}

void TextAdvanced::SetPosition(float x, float y)
{
	m_position = glm::vec2(x, y);
}

void TextAdvanced::SetText(const std::string & text)
{
	m_string = text;
	m_text.SetText(m_string);

	m_text.SetSize(m_string.size() * (int)(m_fontSize / 2.0f), m_fontSize);
}

void TextAdvanced::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_text.SetColor(r, g, b);
}

void TextAdvanced::SetFont(const std::string & fontIndex)
{
	m_text.SetFont(fontIndex);
}

void TextAdvanced::SetPivot(const Pivot pivot)
{
	m_pivot = pivot;
}

int TextAdvanced::GetTextSize()
{
	return m_fontSize;
}

float TextAdvanced::GetTextWidth()
{
	return m_string.size() * (m_fontSize / 2.0f);
}

size_t TextAdvanced::GetTextLength()
{
	return m_string.size();
}

glm::vec2 TextAdvanced::GetPosition()
{
	return m_position;
}

void TextAdvanced::Draw()
{
	glm::vec2 fontDimension = glm::vec2(m_string.size() * (m_fontSize / 2.0f), m_fontSize);

	glm::vec2 calculatedPos;

	switch (m_pivot)
	{
	case TextAdvanced::TOP_LEFT:
		calculatedPos = m_position;
		break;

	case TextAdvanced::TOP_RIGHT:
		fontDimension.y = 0.0f;
		calculatedPos = m_position - fontDimension;
		break;

	case TextAdvanced::TOP_MIDDLE:
		fontDimension.y = 0.0f;
		calculatedPos = m_position - (fontDimension / 2.0f);
		break;

	case TextAdvanced::MIDDLE_LEFT:
		fontDimension.x = 0.0f;
		calculatedPos = m_position - (fontDimension / 2.0f);
		break;

	case TextAdvanced::CENTER:
		calculatedPos = m_position - (fontDimension / 2.0f);
		break;

	case TextAdvanced::MIDDLE_RIGHT:
		fontDimension.y /= 2.0f;
		calculatedPos = m_position - fontDimension;
		break;

	case TextAdvanced::BOTTOM_LEFT:
		fontDimension.x = 0.0f;
		calculatedPos = m_position - fontDimension;
		break;

	case TextAdvanced::BOTTOM_RIGHT:
		calculatedPos = m_position - fontDimension;
		break;

	case TextAdvanced::BOTTOM_MIDDLE:
		fontDimension.x /= 2.0f;
		calculatedPos = m_position - fontDimension;
		break;

	default:
		break;
	}

	//m_position = calculatedPos;
	
	m_text.Draw((int)calculatedPos.x, (int)calculatedPos.y);
}
