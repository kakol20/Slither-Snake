#include "EndState.h"

#include "Game.h"

EndState::EndState()
{
	m_previousState = nullptr;
	m_keyDown = false;

	//m_keyPressed = 0;

	//m_finalScore = 0;
}

EndState::EndState(GameState* prevState)
{
	m_previousState = prevState;
	m_keyDown = false;

	//m_keyPressed = 0;


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

	m_gameOver.SetFont("INTRO_FONT");
	m_gameOver.SetText("Game Over!");
	m_gameOver.SetFontSize(200);
	m_gameOver.SetColor(255, 250, 205);
	m_gameOver.SetPivot(TextAdvanced::BOTTOM_MIDDLE);
	m_gameOver.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_restart.SetFont("INTRO_FONT");
	m_restart.SetText("Tab To Restart Game");
	float size = (m_gameOver.GetTextWidth() / (float)m_restart.GetTextLength()) * 2.0f;
	m_restart.SetFontSize((int)size);
	m_restart.SetColor(255, 250, 205);
	m_restart.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_restart.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_exit.SetFont("INTRO_FONT");
	m_exit.SetText("Escape To Exit Game");
	size = (m_restart.GetTextWidth() / (float)m_exit.GetTextLength()) * 2.0f;
	m_exit.SetFontSize((int)size);
	m_exit.SetColor(255, 250, 205);
	m_exit.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_exit.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, (TheScreen::Instance()->GetScreenSize().y / 2.0f) + (float)m_restart.GetTextSize());
}

void EndState::Update(float dt)
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	// keys must be pressed and not held down to prevent keys from affecting other states

	if (keys[SDL_SCANCODE_ESCAPE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_ESCAPE;
	}

	if (!keys[SDL_SCANCODE_ESCAPE] && m_keyDown && m_keyPressed == SDL_SCANCODE_ESCAPE)
	{
		m_isAlive = false;
		m_isActive = false;
	}

	if (keys[SDL_SCANCODE_TAB])
	{
		MenuState * temp = new MenuState(this);
		temp->Load();

		m_isAlive = false;
		m_isActive = false;

		TheGame::Instance()->ChangeState(temp);
		temp = nullptr;
	}

	m_timeElapsed += dt;
}

void EndState::Draw()
{
	m_background.Draw();

	m_gameOver.Draw();
	m_restart.Draw();
	m_exit.Draw();
}

void EndState::Unload()
{
	std::cout << "\nUnloading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;
	m_background.Unload();
}
