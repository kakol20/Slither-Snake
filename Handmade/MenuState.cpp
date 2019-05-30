#include "MenuState.h"

#include "Game.h"

MenuState::MenuState()
{
	m_previousState = nullptr;
	m_isAlive = true;
	m_isActive = true;

	m_timeElapsed = 0.0f;
}

MenuState::MenuState(GameState * prevState)
{
	m_previousState = prevState;

	m_timeElapsed = prevState->GetTimeElapsed();

	m_isAlive = true;
	m_isActive = true;

	m_timeElapsed = 0.0f;
}

MenuState::~MenuState()
{
}

void MenuState::Load()
{
	std::cout << "\nLoading MenuState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/Menu.png", "MENU_BG", 1920, 1080);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;
	//m_isVisible = true;

	m_title.SetFont("INTRO_FONT");
	m_instructions.SetFont("INTRO_FONT");

	m_title.SetText("SLITHER SNAKE");
	m_title.SetFontSize(200);
	m_title.SetColor(200, 247, 197);
	m_title.SetPivot(TextAdvanced::BOTTOM_MIDDLE);
	m_title.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_instructions.SetText("Press Space To Start");
	float size = (m_title.GetTextWidth() / (float)m_instructions.GetTextLength()) * 2.0f;
	m_instructions.SetFontSize((int)size);
	m_instructions.SetColor(200, 247, 197);
	m_instructions.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_instructions.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);
}

void MenuState::Update(float dt)
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_SPACE]) // when the space bar is pressed go to the game
	{
		PlayState * temp = new PlayState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;
		m_isAlive = false;
		m_isActive = false;
	}

	//if escape key is pressed flag game to end
	if (keys[SDL_SCANCODE_ESCAPE])
	{
		m_isAlive = false;
		m_isActive = false;

		/*EndState * temp = new EndState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);*/

		/*temp = nullptr;*/
	}

	m_timeElapsed += dt;
}

void MenuState::Draw()
{
	m_background.Draw();

	m_title.Draw();
	m_instructions.Draw();
}

void MenuState::Unload()
{
	std::cout << "\nUnloading MenuState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Unload();
}
