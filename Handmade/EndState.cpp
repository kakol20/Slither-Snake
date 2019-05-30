#include "EndState.h"

#include "Game.h"

EndState::EndState()
{
	m_previousState = nullptr;
	m_keyDown = false;

	m_keyPressed = 0;

	//m_finalScore = 0;
}

EndState::EndState(GameState* prevState)
{
	m_previousState = prevState;
	m_keyDown = false;

	m_keyPressed = 0;

	////m_finalScore = 0;

	m_finishedGame = false;

	/*if (dynamic_cast<PlayState*>(prevState))
	{
		m_finalScore = dynamic_cast<PlayState*>(prevState)->GetScore();
		m_finalTimeScore = dynamic_cast<PlayState*>(prevState)->GetTimeScore();

		m_finishedGame = true;
	}*/

	m_timeElapsed = prevState->GetTimeElapsed();
}


EndState::~EndState()
{
}

void EndState::Load()
{
	std::cout << "\nLoading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/End.png", "END_BG", 1920, 1080);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;

	/*m_finalScoreDisplay.SetFont("INTRO_FONT");
	m_finalScoreDisplay.SetColor(255, 255, 255);
	std::string finalScoreText = "Final Score: " + std::to_string(m_finalScore);
	m_finalScoreDisplay.SetSize(25 * finalScoreText.size(), 50);
	m_finalScoreDisplay.SetText(finalScoreText);*/
}

void EndState::Update(float dt)
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	m_timeElapsed += dt;
}

void EndState::Draw()
{
	m_background.Draw();

	//m_finalScoreDisplay.Draw(50, 50);
}

void EndState::Unload()
{
	std::cout << "\nUnloading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;
	m_background.Unload();
}
