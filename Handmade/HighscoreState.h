#pragma once
#include "GameState.h"

#include "GameState.h"

#include <vector>
#include <queue>

#include <fstream>

#include "InputManager.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include "GameState.h"

#include "Background.h"

//#include "PlayState.h"
#include "EndState.h"
#include "SetNameState.h"

#include "TextAdvanced.h"

#include "Tools.h"

struct HighScore
{
	std::string playerName;
	int score;

	bool operator<(const HighScore & rhs) const { return score < rhs.score; };
	bool operator>(const HighScore & rhs) const { return score > rhs.score; };
};

class HighscoreState :
	public GameState
{
public:
	HighscoreState();
	HighscoreState(GameState * prevState);
	virtual ~HighscoreState();

	virtual void Load();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Unload();

private:

	std::vector<HighScore> m_scores;

	int m_topIndex;
	int m_bottomIndex;
	int m_highScoreDisplayMax;


	Background m_background;

	TextAdvanced m_title;
	TextAdvanced m_spaceTo;

	bool m_keyDown;
	SDL_Scancode m_keyPressed;

	std::vector<TextAdvanced*> m_scoreDisplay;
};

