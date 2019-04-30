#include "TextAdvanced.h"



TextAdvanced::TextAdvanced()
{
	m_fontSize = 50;
	m_string = "N/A";
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

	m_text.SetSize(m_string.size() * (m_fontSize / 2), m_fontSize);
}

void TextAdvanced::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_text.SetColor(r, g, b);
}

void TextAdvanced::SetFont(const std::string & fontIndex)
{
	m_text.SetFont(fontIndex);
}

void TextAdvanced::Draw()
{
	m_text.Draw((int)m_position.x, (int)m_position.y);
}
