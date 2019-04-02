#include "PlayState.h"

#include "Game.h"

PlayState::PlayState()
{
	
}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	TheInput::Instance()->SetMouseCursorType(InputManager::CROSSHAIR);

	// snake segment creation
	for (int i = 0; i < 2; i++)
	{
		m_segments.push_back(new Segment);
	}
}

void PlayState::Update()
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	// Updating mouse information
	m_mousePos = TheInput::Instance()->GetMousePosition();
	if (TheInput::Instance()->GetLeftButtonState() == InputManager::DOWN)
	{
		m_mouseDown = true;
	}

	if (m_mouseDown && TheInput::Instance()->GetLeftButtonState() == InputManager::UP)
	{
		m_segments.push_back(new Segment);

		glm::vec3 temp = m_segments[m_segments.size() - 1]->GetPosition();

		m_segments[m_segments.size() - 1]->SetPosition(temp.x, temp.y);

		m_mouseDown = false;
	}

	// Updating snake segments
	for (auto it = m_segments.begin(); it != m_segments.end(); it++)
	{
		if (it == m_segments.begin()) // head of the snake
		{
			(*it)->Move(m_mousePos);
		}
		else
		{
			auto prev = it;
			prev--; // the segment that it's following

			glm::vec3 prevPos = (*prev)->GetPosition();
			(*it)->Move(glm::vec2(prevPos.x, prevPos.y));
		}
	}
}

void PlayState::Draw()
{
	for (auto it = m_segments.begin(); it != m_segments.end(); it++)
	{
		(*it)->Draw();
	}
}

void PlayState::Unload()
{
	for (auto it = m_segments.begin(); it != m_segments.end(); it++)
	{
		if (*it != nullptr)
		{
			(*it)->Unload();
			delete *it;
		}
	}

	
}
