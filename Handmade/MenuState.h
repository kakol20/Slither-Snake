#pragma once

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

class MenuState : public GameState
{
public:
	MenuState();
	MenuState(GameState * prevState);
	virtual ~MenuState();

	virtual void Load();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Unload();

private:

	Background m_background;

	TextAdvanced m_title;
	TextAdvanced m_instructions;
};
