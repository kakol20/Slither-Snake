#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	GameState() {};
	GameState(GameState * prevState) {};
	virtual ~GameState() = 0 {};
	
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;

	bool IsAlive() const { return m_isAlive; };
	bool IsActive() const { return m_isActive; };
	//bool IsVisible() const { return m_isVisible; };

	void SetAlive(bool flag) { m_isAlive = flag; };
	void SetActive(bool flag) { m_isActive = flag; };

	void setPreviousState(GameState * state) { m_previousState = state; };

protected:
	bool m_isAlive;
	bool m_isActive;
	//bool m_isVisible;

	GameState * m_previousState;
};

#endif // !GAMESTATE_H
