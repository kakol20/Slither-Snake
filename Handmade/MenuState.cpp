#include "MenuState.h"

#include "Game.h"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::Load()
{
	m_background.Load("Assets/Textures/Menu.png", "MENU_BG", 1600, 900);
	m_background.SetVisible(true);
}

void MenuState::Update()
{
	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_SPACE])
	{
		TheGame::Instance()->m_state = TheGame::Instance()->PLAY;
	}
}

void MenuState::Draw()
{
	m_background.Draw();
}

void MenuState::Unload()
{
	m_background.Unload();
}
