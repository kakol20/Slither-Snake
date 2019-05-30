#include "PlayState.h"

#include "Game.h"

PlayState::PlayState()
{
	m_mouseDown = false;
	m_mousePos = glm::vec2(0.0f);

	m_score = 0;

	m_elapsedTimePS = 0.0;
}

PlayState::PlayState(GameState * prevState)
{
	m_mouseDown = false;

	m_previousState = prevState;

	m_score = 0;
	m_mousePos = glm::vec2(0.0f);

	m_timeElapsed = prevState->GetTimeElapsed();

}

PlayState::~PlayState()
{
}

void PlayState::Load()
{
	//TheInput::Instance()->SetMouseCursorType(InputManager::CROSSHAIR);

	std::cout << "\nLoading PlayState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_isAlive = true;
	m_isActive = true;

	glm::vec2 middle = TheScreen::Instance()->GetScreenSize() / 2.0f;
	// snake segment creation
	for (int i = 0; i < 2; i++)
	{
		m_segments.push_back(new Segment(glm::vec3(middle, 0.0f)));
	}

	// LOAD BACKGROUND
	m_background.Load("Assets/Textures/Play.png", "PLAY_BG", 1920, 1080);
	m_background.SetVisible(true);

	// LOAD TEXT

	m_scoreDisplay.SetFont("INTRO_FONT");
	m_scoreDisplay.SetColor(224, 255, 255);
	m_scoreDisplay.SetFontSize(50);
	m_scoreDisplay.SetPosition(25, 25);

	m_objectiveDisplay.SetFont("INTRO_FONT");
	m_objectiveDisplay.SetColor(224, 255, 255);
	//std::string objectiveText = "Eat apples to gain a segment";
	//m_objectiveDisplay.SetSize(objectiveText.size() * 25, 50);
	m_objectiveDisplay.SetText("Eat apples to gain a segment");
	m_objectiveDisplay.SetFontSize(50);
	m_objectiveDisplay.SetPosition(25.0f, TheScreen::Instance()->GetScreenSize().y - 75.0f);


	m_gameOverDisplay.SetFont("INTRO_FONT");
	m_gameOverDisplay.SetColor(224, 255, 255);
	//m_gameOverDisplay.SetSize(gameOverText.size() * 25, 50);
	m_gameOverDisplay.SetText("Avoid contact with own body");
	m_gameOverDisplay.SetPosition(25.0f, TheScreen::Instance()->GetScreenSize().y - 125.0f);
	m_gameOverDisplay.SetFontSize(50);

	m_timeDisplay.SetFont("INTRO_FONT");
	m_timeDisplay.SetColor(224, 255, 255);
	m_timeDisplay.SetFontSize(50);
	m_timeDisplay.SetPosition(25.0f, 75.0f);

	m_cumulativeDT = 0;

	m_gameOver = false;
}

void PlayState::Update(float dt)
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (m_isActive)
	{
		if (keys[SDL_SCANCODE_ESCAPE])
		{
			m_isActive = false;

			PauseState * temp = new PauseState(this);
			temp->Load();

			TheGame::Instance()->AddState(temp);
			temp = nullptr;
		}
		else
		{
			// Updating mouse information
			m_mousePos = TheInput::Instance()->GetMousePosition();

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

			// Updating game objects
			for (size_t i = 0; i < m_segments.size(); i++)
			{
				m_segments[i]->Update();
			}
			m_apple.Update();

			// Checking collision with body

			if (m_segments.size() >= 7)
			{
				for (size_t i = 6; i < m_segments.size(); i++)
				{
					if (m_segments.front()->GetBound().IsColliding(m_segments[i]->GetBound()))
					{
						m_isAlive = false;
						m_isActive = false;

						m_gameOver = true;
					}
				}
			}

			// check for game over
			if (!m_isAlive && m_gameOver)
			{
				SetNameState* temp = new SetNameState(this);
				temp->Load();

				TheGame::Instance()->ChangeState(temp);

				temp = nullptr;
			}
			else
			{
				// Checking collision with apple
				if (m_segments.front()->GetBound().IsColliding(m_apple.GetBound()))
				{
					size_t last = m_segments.size() - 1;

					glm::vec3 temp = m_segments[0]->GetPosition() - m_segments[last]->GetPosition();
					temp = glm::normalize(temp) * glm::vec3(m_segments[0]->GetSize(), 20.0f); // spawn segment 20 pixels away from the segment it's following

					m_segments.push_back(new Segment(m_segments[last]->GetPosition() - temp));

					m_apple.SetActive(false);

					m_score++;
				}

				m_elapsedTimePS += dt;
			}

			// Updating text
			std::string scoreText = "Score: " + std::to_string(m_score);
			//m_scoreDisplay.SetSize(25 * scoreText.size(), 50);
			m_scoreDisplay.SetText(scoreText);


			if (m_cumulativeDT > 1000.0f) // update time every 1 second
			{
				std::string timeText = "Time: " + std::to_string((int)(m_elapsedTimePS * 0.001f));
				m_timeDisplay.SetText(timeText);

				m_cumulativeDT = 0.0f;
			}
			m_cumulativeDT += dt;
		}
	}

	m_timeElapsed += dt;
}

void PlayState::Draw()
{
	m_background.Draw();

	m_timeDisplay.Draw();
	m_scoreDisplay.Draw();
	m_gameOverDisplay.Draw();
	m_objectiveDisplay.Draw();

	for (size_t i = 0; i < m_segments.size(); i++)
	{
		m_segments[i]->Draw();
	}

	m_apple.Draw();
}

void PlayState::Unload()
{
	std::cout << "\nUnloading PlayState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;


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

	m_background.Unload();
}

int PlayState::GetScore() const
{
	return m_score;
}

float PlayState::GetTimeScore() const
{
	return m_elapsedTimePS / 1000.0f;
}
