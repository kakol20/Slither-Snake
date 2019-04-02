#include "Game.h"

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

	//m_gameState.Load();

	PLAY = new PlayState;
	PLAY->Load();

	MENU = new MenuState;
	MENU->Load();

	m_state = MENU;

	return true;
}

bool Game::Run()
{
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

	//if escape key is pressed flag game to end
	if (keys[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}

	// UPDATE AND DRAW

	if (m_state == nullptr)
	{
		return false;
	}
	else
	{
		m_state->Update();
		m_state->Draw();
	}

	//draw screen by swapping SDL frame buffer
	TheScreen::Instance()->Draw();

	return true;
}

void Game::Shutdown()
{
	//m_gameState.Unload();

	if (PLAY != nullptr)
	{
		PLAY->Unload();
		delete PLAY;
		PLAY = nullptr;
	}

	if (MENU != nullptr)
	{
		MENU->Unload();
		delete MENU;
		MENU = nullptr;
	}

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
