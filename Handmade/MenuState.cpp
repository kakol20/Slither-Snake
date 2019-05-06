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
}

MenuState::~MenuState()
{
}

void MenuState::Load()
{
	std::cout << "\nLoading MenuState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/Menu.png", "MENU_BG", 1600, 900);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;
	//m_isVisible = true;
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

		EndState * temp = new EndState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;
	}

	m_timeElapsed += dt;
}

void MenuState::Draw()
{
	m_background.Draw();
}

void MenuState::Unload()
{
	std::cout << "\nUnloading MenuState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Unload();
}
