#pragma once
#include "GameState.h"

#include <vector>

#include <fstream>

#include "InputManager.h"
#include "AudioManager.h"
#include "TextureManager.h"

#include "GameState.h"

#include "Background.h"

#include "PlayState.h"
//#include "EndState.h"

#include "TextAdvanced.h"

class PauseState :
	public GameState
{
public:
	PauseState();
	PauseState(GameState * prevState);
	virtual ~PauseState();

	virtual void Load();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Unload();

private:

	TextAdvanced m_gamePaused;
	TextAdvanced m_return;
	TextAdvanced m_exit;

	Background m_background;
};

