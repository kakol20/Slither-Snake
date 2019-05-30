#include "PauseState.h"



PauseState::PauseState()
{
}

PauseState::PauseState(GameState * prevState)
{
	m_previousState = prevState;
}


PauseState::~PauseState()
{
}

void PauseState::Load()
{
	std::cout << "\nLoading PauseState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/Pause.png", "PAUSE_BG", 1920, 1080);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isAlive = true;

	m_gamePaused.SetFont("INTRO_FONT");
	m_gamePaused.SetText("GAME PAUSED");
	m_gamePaused.SetFontSize(200);
	m_gamePaused.SetColor(224, 255, 255);
	m_gamePaused.SetPivot(TextAdvanced::BOTTOM_MIDDLE);
	m_gamePaused.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_exit.SetFont("INTRO_FONT");
	m_exit.SetText("Escape To Exit Game");
	float size = (m_gamePaused.GetTextWidth() / (float)m_exit.GetTextLength()) * 2.0f;
	m_exit.SetFontSize((int)size);
	m_exit.SetColor(224, 255, 255);
	m_exit.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_exit.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_return.SetFont("INTRO_FONT");
	m_return.SetText("Tab To Resume Game");
	size = (m_exit.GetTextWidth() / (float)m_return.GetTextLength()) * 2.0f;
	m_return.SetFontSize((int)size);
	m_return.SetColor(224, 255, 255);
	m_return.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_return.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, (TheScreen::Instance()->GetScreenSize().y / 2.0f) + (float)m_exit.GetTextSize());
}

void PauseState::Update(float dt)
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_TAB]) // when the tab is pressed resume game
	{
		m_previousState->SetActive(true);

		m_isActive = false;
		m_isAlive = false;
	}

	if (keys[SDL_SCANCODE_ESCAPE])
	{
		m_isActive = false;
		m_isAlive = false;
		m_previousState->SetAlive(false);
		m_previousState->SetActive(false);
	}

	m_timeElapsed += dt;
}

void PauseState::Draw()
{
	m_background.Draw();

	m_gamePaused.Draw();
	m_exit.Draw();
	m_return.Draw();
}

void PauseState::Unload()
{
	std::cout << "\nUnloading PauseState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Unload();
}
