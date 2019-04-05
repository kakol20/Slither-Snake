#include "EndState.h"

#include "Game.h"

EndState::EndState()
{
	m_previousState = nullptr;
	m_keyDown = false;

	m_keyPressed = 0;

	m_finalScore = 0;
}

EndState::EndState(GameState* prevState)
{
	m_previousState = prevState;
	m_keyDown = false;

	m_keyPressed = 0;

	m_finalScore = 0;

	if (dynamic_cast<PlayState*>(prevState))
	{
		m_finalScore = dynamic_cast<PlayState*>(prevState)->GetScore();
	}
}


EndState::~EndState()
{
}

void EndState::Load()
{
	std::cout << "\nLoading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/End.png", "END_BG", 1600, 900);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;

	m_finalScoreDisplay.SetFont("INTRO_FONT");
	m_finalScoreDisplay.SetColor(255, 255, 255);
	std::string finalScoreText = "Final Score: " + std::to_string(m_finalScore);
	m_finalScoreDisplay.SetSize(25 * finalScoreText.size(), 50);
	m_finalScoreDisplay.SetText(finalScoreText);
}

void EndState::Update()
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_SPACE] && !m_keyDown) // to avoid key holding effecting the next game state
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_SPACE;
	}
	else if (keys[SDL_SCANCODE_ESCAPE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_ESCAPE;
	}

	if (!keys[SDL_SCANCODE_SPACE] && m_keyDown && m_keyPressed == SDL_SCANCODE_SPACE) // go to the menu when space bar pressed
	{
		MenuState* temp = new MenuState;
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;
		m_isAlive = false;
		m_isActive = false;

		m_keyDown = false;
	}
	else if (!keys[SDL_SCANCODE_ESCAPE] && m_keyDown && m_keyPressed == SDL_SCANCODE_ESCAPE) // exit game
	{
		m_isAlive = false;
		m_isActive = false;
	}
}

void EndState::Draw()
{
	m_background.Draw();

	m_finalScoreDisplay.Draw(50, 50);
}

void EndState::Unload()
{
	std::cout << "\nUnloading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;
	m_background.Unload();
}
