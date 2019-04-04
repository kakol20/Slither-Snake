#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL.h>
#include <iostream>

#include <vector>
#include <gtc/random.hpp>
#include <algorithm>

#include "InputManager.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include "GameState.h"

//#include "Background.h"
#include "Segment.h"
#include "Apple.h"

#include "Text.h"

class PlayState : public GameState
{
public:
	PlayState();
	PlayState(GameState * prevState);
	virtual ~PlayState();

	virtual void Load();
	virtual void Update();
	virtual void Draw();
	virtual void Unload();

private:
	bool m_mouseDown;
	glm::vec2 m_mousePos;

	std::vector<Segment*> m_segments;

	Apple m_apple;

	int m_score;

	Text m_scoreDisplay;
};

#endif // !PLAYSTATE_H
