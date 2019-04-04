#include "EndState.h"

#include "Game.h"

EndState::EndState()
{
	m_previousState = nullptr;
	m_keyDown = false;

	m_keyPressed = 0;
}

EndState::EndState(GameState* prevState)
{
	m_previousState = prevState;
	m_keyDown = false;

	m_keyPressed = 0;
}


EndState::~EndState()
{
}

void EndState::Load()
{
	m_background.Load("Assets/Textures/End.png", "END_BG", 1600, 900);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;
}

void EndState::Update()
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_SPACE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_SPACE;
	}
	else if (keys[SDL_SCANCODE_ESCAPE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_ESCAPE;
	}

	if (!keys[SDL_SCANCODE_SPACE] && m_keyDown && m_keyPressed == SDL_SCANCODE_SPACE)
	{
		MenuState* temp = new MenuState;
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;
		m_isAlive = false;
		m_isActive = false;

		m_keyDown = false;
	}
	else if (!keys[SDL_SCANCODE_ESCAPE] && m_keyDown && m_keyPressed == SDL_SCANCODE_ESCAPE)
	{
		m_isAlive = false;
		m_isActive = false;
	}
}

void EndState::Draw()
{
	m_background.Draw();
}

void EndState::Unload()
{
	m_background.Unload();
}
