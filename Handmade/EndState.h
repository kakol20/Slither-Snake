#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
//#include <deque>

#include "GameState.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "Text.h"

#include "Background.h"

#include "MenuState.h"

struct HighScore
{
	int playerID;
	int score;
	float timeSpent;

	bool operator<(const HighScore & rhs) const { return score < rhs.score; };
	bool operator>(const HighScore & rhs) const { return score > rhs.score; };
};

class EndState : public GameState
{
public:
	EndState();
	EndState(GameState* prevState);
	virtual ~EndState();

	virtual void Load();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Unload();

private:
	Background m_background;

	bool m_keyDown;
	int m_keyPressed;

	bool m_finishedGame;

	int m_finalScore;

	float m_finalTimeScore;

	Text m_finalScoreDisplay;

	bool SortScores(HighScore left, HighScore right) { return left.score > right.score; };

	void SaveScore();

};

