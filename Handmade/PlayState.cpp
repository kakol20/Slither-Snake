#include "PlayState.h"

#include "Game.h"

PlayState::PlayState(GameState * prevState)
{
	m_previousState = prevState;
}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	TheInput::Instance()->SetMouseCursorType(InputManager::CROSSHAIR);

	m_isAlive = true;
	m_isActive = true;
	//m_isVisible = true;

	// snake segment creation
	for (int i = 0; i < 2; i++)
	{
		m_segments.push_back(new Segment);
	}
}

void PlayState::Update()
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_ESCAPE])
	{
		m_isAlive = false;
	}
	else
	{
		// Updating mouse information
		m_mousePos = TheInput::Instance()->GetMousePosition();
		if (TheInput::Instance()->GetLeftButtonState() == InputManager::DOWN)
		{
			m_mouseDown = true;
		}

		// Adding a segment
		if (m_mouseDown && TheInput::Instance()->GetLeftButtonState() == InputManager::UP)
		{
			auto it = m_segments.end() - 1;
			auto head = m_segments.begin();
			glm::vec3 temp = (*head)->GetPosition() - (*it)->GetPosition();
			temp = glm::normalize(temp) * 20.0f;

			m_segments.push_back(new Segment((*it)->GetPosition() - temp));

			temp = m_segments[m_segments.size() - 1]->GetPosition();

			//m_segments[m_segments.size() - 1]->SetPosition(temp.x, temp.y);

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
