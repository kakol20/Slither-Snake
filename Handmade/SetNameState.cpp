#include "SetNameState.h"



SetNameState::SetNameState()
{
	
}

SetNameState::SetNameState(GameState * prevState)
{
	m_letters = {
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
	};

	m_name = {
		0, 0, 0
	};

	m_chosen = 0;

	m_finalScore;

	if (dynamic_cast<PlayState*>(prevState)) // getting scores
	{
		m_finalScore = dynamic_cast<PlayState*>(prevState)->GetScore();
		m_finalTimeScore = dynamic_cast<PlayState*>(prevState)->GetTimeScore();
	}

	m_timeElapsed = prevState->GetTimeElapsed();
}


SetNameState::~SetNameState()
{
}

void SetNameState::Load()
{
	std::cout << "\nLoading SetNameState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;
	m_background.Load("Assets/Textures/SetName.png", "SET_NAME_BG", 1920, 1080);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;

	m_name1.SetFont("INTRO_FONT");
	m_name1.SetText(m_letters[m_name[0]]);
	m_name1.SetFontSize(200);
	m_name1.SetColor(255, 255, 255);
	m_name1.SetPivot(TextAdvanced::BOTTOM_RIGHT);

	m_name2.SetFont("INTRO_FONT");
	m_name2.SetText(m_letters[m_name[1]]);
	m_name2.SetFontSize(200);
	m_name2.SetColor(255, 255, 255);
	m_name2.SetPivot(TextAdvanced::BOTTOM_MIDDLE);

	m_name3.SetFont("INTRO_FONT");
	m_name3.SetText(m_letters[m_name[2]]);
	m_name3.SetFontSize(200);
	m_name3.SetColor(255, 255, 255);
	m_name3.SetPivot(TextAdvanced::BOTTOM_LEFT);

	m_name2.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);
	m_name1.SetPosition((TheScreen::Instance()->GetScreenSize().x / 2.0f) - (m_name2.GetTextWidth()), TheScreen::Instance()->GetScreenSize().y / 2.0f);
	m_name3.SetPosition((TheScreen::Instance()->GetScreenSize().x / 2.0f) + (m_name2.GetTextWidth()), TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_finalScoreText.SetFont("INTRO_FONT");
	m_finalScoreText.SetText("Final Score: " + std::to_string(m_finalScore));
	m_finalScoreText.SetFontSize(50);
	m_finalScoreText.SetColor(255, 255, 255);
	m_finalScoreText.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_finalScoreText.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y / 2.0f);

	m_pressEnter.SetFont("INTRO_FONT");
	m_pressEnter.SetText("Enter to confirm name");
	float size = (m_finalScoreText.GetTextWidth() / (float)m_pressEnter.GetTextLength()) * 2.0f;
	m_pressEnter.SetFontSize((int)size);
	m_pressEnter.SetColor(255, 255, 255);
	m_pressEnter.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_pressEnter.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, (TheScreen::Instance()->GetScreenSize().y / 2.0f) + (float)m_finalScoreText.GetTextSize());
}

void SetNameState::Update(float dt)
{
	int change = 0;
	int changeName = 0;

	const Uint8 * keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_LEFT] && !m_keyHeld)
	{
		m_keyHeld = true;
		m_keyPressed = SDL_SCANCODE_LEFT;
	}
	
	if (keys[SDL_SCANCODE_RIGHT] && !m_keyHeld)
	{
		m_keyHeld = true;
		m_keyPressed = SDL_SCANCODE_RIGHT;
	}

	if (keys[SDL_SCANCODE_UP] && !m_keyHeld)
	{
		m_keyHeld = true;
		m_keyPressed = SDL_SCANCODE_UP;
	}

	if (keys[SDL_SCANCODE_DOWN] && !m_keyHeld)
	{
		m_keyHeld = true;
		m_keyPressed = SDL_SCANCODE_DOWN;
	}

	//For key toggling
	if (!keys[SDL_SCANCODE_LEFT] && m_keyPressed == SDL_SCANCODE_LEFT && m_keyHeld)
	{
		change--;
		m_keyHeld = false;
	}

	if (!keys[SDL_SCANCODE_RIGHT] && m_keyPressed == SDL_SCANCODE_RIGHT && m_keyHeld)
	{
		change++;
		m_keyHeld = false;
	}

	if (!keys[SDL_SCANCODE_UP] && m_keyPressed == SDL_SCANCODE_UP && m_keyHeld)
	{
		changeName--;
		m_keyHeld = false;
	}

	if (!keys[SDL_SCANCODE_DOWN] && m_keyPressed == SDL_SCANCODE_DOWN && m_keyHeld)
	{
		changeName++;
		m_keyHeld = false;
	}

	m_chosen += change;
	if (m_chosen < 0) m_chosen = 2;
	if (m_chosen > 2) m_chosen = 0;

	// chosing which letter to change it to
	m_name[m_chosen] += changeName;

	if (m_name[m_chosen] < 0) m_name[m_chosen] = m_letters.size() - 1;
	if (m_name[m_chosen] > (int)(m_letters.size() - 1)) m_name[m_chosen] = 0;

	// choosing which part of name to change
	if (m_chosen == 0)
	{
		m_name1.SetColor(127, 255, 212);
		m_name2.SetColor(255, 255, 255);
		m_name3.SetColor(255, 255, 255);

		m_name1.SetText(m_letters[m_name[m_chosen]]);
	}
	else if (m_chosen == 1)
	{
		m_name2.SetColor(127, 255, 212);
		m_name1.SetColor(255, 255, 255);
		m_name3.SetColor(255, 255, 255);

		m_name2.SetText(m_letters[m_name[m_chosen]]);
	}
	else if (m_chosen == 2)
	{
		m_name3.SetColor(127, 255, 212);
		m_name1.SetColor(255, 255, 255);
		m_name2.SetColor(255, 255, 255);

		m_name3.SetText(m_letters[m_name[m_chosen]]);
	}

	// Check if enter pressed
	if (keys[SDL_SCANCODE_RETURN])
	{
		HighscoreState * temp = new HighscoreState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		m_isAlive = false;
		m_isActive = false;
	}
}

void SetNameState::Draw()
{
	m_background.Draw();

	m_name2.Draw();
	m_name1.Draw();
	m_name3.Draw();

	m_finalScoreText.Draw();
	m_pressEnter.Draw();
}

void SetNameState::Unload()
{
	std::cout << "\nUnloading SetNameState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Unload();
}

std::string SetNameState::GetFullName()
{
	return m_letters[m_name[0]] + m_letters[m_name[1]] + m_letters[m_name[2]];
}

int SetNameState::GetScore()
{
	return m_finalScore;
}
