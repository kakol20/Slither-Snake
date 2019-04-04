#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <deque>

#include "Singleton.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"

#include "GameState.h"

class Game
{
public:

	friend class Singleton<Game>;

	bool Initialise(const std::string & name, int screenWidth, int screenHeight, bool fullscreen = false);
	bool Run();
	void Shutdown();

	void AddState(GameState * state);
	void ChangeState(GameState * state);

private:

	Game() {};
	Game(const Game & copyGame);
	Game & operator=(const Game & copyGame);

	std::deque<GameState*> m_states;

	void RemoveState();

	float m_deltaTime;
};

typedef Singleton<Game> TheGame;

#endif // !GAME_H
