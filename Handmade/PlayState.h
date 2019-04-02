#ifndef PLAYSTATE_H
#define PLAYSTATE_H

//#include "SFX.h"
//#include "Text.h"
//#include "Audio.h"
//#include "Sprite.h"
//#include "Animation.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "TextureManager.h"


#include <SDL.h>
#include <iostream>

//#include "Background.h"
#include "Segment.h"
#include "GameState.h"

#include <vector>

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState();

	virtual void Load();
	virtual void Update();
	virtual void Draw();
	virtual void Unload();

private:
	bool m_mouseDown;
	glm::vec2 m_mousePos;

	std::vector<Segment*> m_segments;
};

#endif // !PLAYSTATE_H
