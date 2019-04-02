#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	GameState() {};
	virtual ~GameState() = 0 {};
	
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;
};

#endif // !GAMESTATE_H
