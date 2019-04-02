#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>

#include "Singleton.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"

#include "PlayState.h"
#include "MenuState.h"

class Game
{
public:

	friend class Singleton<Game>;

	PlayState * PLAY;
	MenuState * MENU;
	GameState * m_state;

	bool Initialise(const std::string & name, int screenWidth, int screenHeight, bool fullscreen = false);
	bool Run();
	void Shutdown();

private:

	Game() {};
	Game(const Game & copyGame);
	Game & operator=(const Game & copyGame);
};

typedef Singleton<Game> TheGame;

#endif // !GAME_H
