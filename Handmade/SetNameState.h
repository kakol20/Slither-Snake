#pragma once
#include "GameState.h"

#include <vector>

#include <fstream>

#include "InputManager.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include "Game.h"

#include "GameState.h"

#include "Background.h"

#include "PlayState.h"
#include "EndState.h"
#include "HighscoreState.h"

#include "TextAdvanced.h"


class SetNameState :
	public GameState
{
public:
	SetNameState();
	SetNameState(GameState * prevState);
	virtual ~SetNameState();

	virtual void Load();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Unload();

	std::string GetFullName();
	int GetScore();

private:

	std::vector<std::string> m_letters;

	int m_finalScore;
	float m_finalTimeScore;

	std::vector<int> m_name;
	int m_chosen;

	bool m_keyHeld;
	SDL_Scancode m_keyPressed;

	Background m_background;

	TextAdvanced m_name1;
	TextAdvanced m_name2;
	TextAdvanced m_name3;

	TextAdvanced m_finalScoreText;
	TextAdvanced m_pressEnter;
};

