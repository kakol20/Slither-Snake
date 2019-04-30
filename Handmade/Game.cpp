#include "Game.h"

Game::Game()
{
	m_deltaTime = 0.0f;
}

bool Game::Initialise(const std::string & name, int screenWidth, int screenHeight, bool fullscreen)
{
	//initialise game screen and background rendering color
	if (!TheScreen::Instance()->Initialize(name.c_str(), screenWidth, screenHeight, fullscreen))
	{
		return false;
	}
	TheScreen::Instance()->SetClearColor(100, 149, 237);
	
	//initialize audio
	if (!TheAudio::Instance()->Initialize())
	{
		return false;
	}

	if (!TheTexture::Instance()->Initialize())
	{
		return false;
	}

	//m_gameState.Load()
	//m_states.front()->Load();

	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Intro.otf", 600, "INTRO_FONT");

	return true;
}

bool Game::Run()
{
	float startTime = (float)SDL_GetTicks();

	//update screen by clearing SDL frame buffer
	TheScreen::Instance()->Update();

	//update input handling by listening for input events
	TheInput::Instance()->Update();

	//read keyboard state
	const Uint8* keys = nullptr;

	keys = TheInput::Instance()->GetKeyStates();

	//m_gameState.Update(keys);

	//if game window's top right X is clicked flag game to end
	if (TheInput::Instance()->IsXClicked())
	{
		return false;
	}

	// UPDATE AND DRAW

	if (m_states.empty())
	{
		return false;
	}

  	if (m_states.front()->IsActive())
	{
		m_states.front()->Update(m_deltaTime);
	}

	m_states.front()->Draw();

	if (!m_states.front()->IsAlive())
	{
		RemoveState();
	}

	//draw screen by swapping SDL frame buffer
	TheScreen::Instance()->Draw();

	m_deltaTime = SDL_GetTicks() - startTime;

	return true;
}

void Game::Shutdown()
{
	//m_gameState.Unload();

	// UNLOAD
	TheAudio::Instance()->UnloadFromMemory(AudioManager::SFX_AUDIO, AudioManager::ALL_AUDIO);
	TheAudio::Instance()->UnloadFromMemory(AudioManager::MUSIC_AUDIO, AudioManager::ALL_AUDIO);

	TheTexture::Instance()->UnloadFromMemory(TextureManager::FONT_DATA, TextureManager::ALL_DATA);
	TheTexture::Instance()->UnloadFromMemory(TextureManager::TEXTURE_DATA, TextureManager::ALL_DATA);

	TheTexture::Instance()->ShutDown();

	//close down audio 
	TheAudio::Instance()->ShutDown();

	//close down game screen 
	TheScreen::Instance()->ShutDown();
}

void Game::AddState(GameState * state)
{
	m_states.push_front(state);
	//m_states.front()->Load();
}

void Game::ChangeState(GameState * state)
{
	m_states.push_back(state);
	//m_states.back()->Load();
}

void Game::RemoveState()
{
	m_states.front()->Unload();
	delete m_states.front();
	m_states.front() = nullptr;

	m_states.pop_front();
}
