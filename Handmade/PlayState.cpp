#include "PlayState.h"

#include "Game.h"

PlayState::PlayState()
{
	m_mouseDown = false;
	m_mousePos = glm::vec2(0.0f);

	m_score = 0;
}

PlayState::PlayState(GameState * prevState)
{
	m_mouseDown = false;

	m_previousState = prevState;

	m_score = 0;
	m_mousePos = glm::vec2(0.0f);

}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	//TheInput::Instance()->SetMouseCursorType(InputManager::CROSSHAIR);

	m_isAlive = true;
	m_isActive = true;
	//m_isVisible = true
	// snake segment creation
	for (int i = 0; i < 2; i++)
	{
		m_segments.push_back(new Segment);
	}

	// LOAD FONT
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Intro.otf", 600, "INTRO_FONT");

	m_scoreDisplay.SetFont("INTRO_FONT");
	m_scoreDisplay.SetColor(255, 255, 255);
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
		/*if (TheInput::Instance()->GetLeftButtonState() == InputManager::DOWN)
		{
			m_mouseDown = true;
		}*/

		for (size_t i = 0; i < m_segments.size(); i++)
		{
			if (i == 0)
			{
				m_segments[i]->Move(m_mousePos);
			}
			else
			{
				size_t prevI = i - 1;

				glm::vec3 prevPos = m_segments[prevI]->GetPosition();
				m_segments[i]->Move(glm::vec2(prevPos));
			}
		}

		for (size_t i = 0; i < m_segments.size(); i++)
		{
			m_segments[i]->Update();
		}
		m_apple.Update();

		// Checking collision with body
		for (size_t i = 2; i < m_segments.size(); i++)
		{
			if (m_segments.front()->GetBound().IsColliding(m_segments[i]->GetBound()))
			{
				m_isAlive = false;
			}
		}

		// Checking collision with apple
		if (m_segments.front()->GetBound().IsColliding(m_apple.GetBound()))
		{
			size_t last = m_segments.size() - 1;
			
			glm::vec3 temp = m_segments[0]->GetPosition() - m_segments[last]->GetPosition();
			temp = glm::normalize(temp) * glm::vec3(m_segments[0]->GetSize(), 20.0f);

			m_segments.push_back(new Segment(m_segments[last]->GetPosition() - temp));

			m_apple.SetActive(false);

			m_score++;
		}

		// Updating text
		std::string scoreText = "Score: " + std::to_string(m_score);
		m_scoreDisplay.SetSize(25 * scoreText.size(), 50);
		m_scoreDisplay.SetText(scoreText);
	}
}

void PlayState::Draw()
{
	for (size_t i = 0; i < m_segments.size(); i++)
	{
		m_segments[i]->Draw();
	}

	m_apple.Draw();

	m_scoreDisplay.Draw(50, 50);
}

void PlayState::Unload()
{
	/*for (auto it = m_segments.begin(); it != m_segments.end(); it++)
	{
		if (*it != nullptr)
		{
			(*it)->Unload();
			delete *it;
		}
	}*/
	for (size_t i = 0; i < m_segments.size(); i++)
	{
		if (m_segments[i] != nullptr)
		{
			m_segments[i]->Unload();
			delete m_segments[i];
			m_segments[i] = nullptr;
		}
	}

	m_segments.clear();

	m_apple.Unload();
}
