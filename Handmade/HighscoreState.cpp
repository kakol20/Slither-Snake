#include "HighscoreState.h"



HighscoreState::HighscoreState()
{
	
}

HighscoreState::HighscoreState(GameState * prevState)
{
	m_previousState = prevState;

	HighScore currScore;

	if (dynamic_cast<SetNameState *>(prevState))
	{
		currScore.playerName = dynamic_cast<SetNameState *>(prevState)->GetFullName();
		currScore.score = dynamic_cast<SetNameState *>(prevState)->GetScore();
	}

	m_topIndex = 0;
	m_highScoreDisplayMax = 10;
	m_bottomIndex = m_highScoreDisplayMax - 1;

	m_keyDown = false;

	std::fstream file;
	// CHECK IF HIGHSCORE FILE EXISTS

	file.open("Data/high.score", std::ios_base::in | std::ios_base::binary);

	bool exists = true;

	if (!file.is_open())
	{
		file.close();
		file.open("Data/high.score", std::ios_base::out | std::ios_base::binary);
		file.close();
		file.open("Data/high.score", std::ios_base::in | std::ios_base::binary);

		exists = false;
	}

	// Using priority queue to sort scores
	std::priority_queue<HighScore, std::vector<HighScore>, std::less<HighScore>> scoreArray;

	// get size of file
	std::fstream temp("Data/high.score", std::ios_base::binary | std::ios_base::in);
	std::streampos sizeOfFile = 0;
	sizeOfFile = temp.tellg();
	temp.seekg(0, std::ios_base::end);
	sizeOfFile = temp.tellg() - sizeOfFile;
	temp.close();

	std::cout << std::endl << "Size of highscore file: " << std::to_string(sizeOfFile) << std::endl;

	while (exists)
	{
		// if at end of file then break
		std::streampos gPos = file.tellg();
		if (gPos >= sizeOfFile) break;
		
		unsigned int cumulativeSize = sizeof(size_t) + sizeof(int);

		// first part gets the length of the string
		size_t length;

		file.read((char*)&length, sizeof(size_t));

		// second part gets the name
		char * temp = new char[length + 1];
		file.read(temp, length);
		temp[length] = '\0';

		std::string output = temp;

		delete[] temp;

		// third part gets the score
		int score;
		file.read((char*)&score, sizeof(int));

		cumulativeSize += length;

		HighScore input;

		input.playerName = output;
		input.score = score;

		scoreArray.push(input);

		std::cout << gPos << " : " << cumulativeSize << std::endl;
	}
	file.close();

	// push current score
	scoreArray.push(currScore);

	// add ordered scores to member vector container
	while (!scoreArray.empty())
	{
		m_scores.push_back(scoreArray.top());

		std::cout << scoreArray.top().playerName << ": " << scoreArray.top().score << std::endl;

		scoreArray.pop();
	}

	// saving new score to file
	file.open("Data/high.score", std::ios_base::out | std::ios_base::binary);
	for (auto it = m_scores.begin(); it != m_scores.end(); it++)
	{
		std::string name = (*it).playerName;
		size_t size = (*it).playerName.size() * sizeof(char);
		int score = (*it).score;

		file.write((char*)&size, sizeof(size_t)); // save length of string
		file.write(name.c_str(), size); // save string
		file.write((char*)&score, sizeof(int)); // save score
	}
	file.close();
}


HighscoreState::~HighscoreState()
{
}

void HighscoreState::Load()
{
	std::cout << "\nLoading HighscoreState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/HighScore.png", "HIGHSCORE_BG", 1920, 1080);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isAlive = true;

	m_title.SetFont("INTRO_FONT");
	m_title.SetText("Highscores");
	m_title.SetFontSize(100);
	m_title.SetColor(255, 250, 205);
	m_title.SetPivot(TextAdvanced::TOP_MIDDLE);
	m_title.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, 50.0f);

	float top = m_title.GetPosition().y + m_title.GetTextSize();

	for (size_t i = 0; i < m_scores.size(); i++)
	{
		m_scoreDisplay.push_back(new TextAdvanced);

		m_scoreDisplay[i]->SetFont("INTRO_FONT");
		m_scoreDisplay[i]->SetText(m_scores[i].playerName + ": " + std::to_string(m_scores[i].score));
		m_scoreDisplay[i]->SetFontSize(50);
		m_scoreDisplay[i]->SetColor(255, 250, 205);
		m_scoreDisplay[i]->SetPivot(TextAdvanced::TOP_MIDDLE);
		m_scoreDisplay[i]->SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, top);

		top += 50.0f;
	}

	m_spaceTo.SetFont("INTRO_FONT");
	m_spaceTo.SetText("Space to Continue");
	m_spaceTo.SetFontSize(75);
	m_spaceTo.SetColor(255, 250, 205);
	m_spaceTo.SetPivot(TextAdvanced::BOTTOM_MIDDLE);
	m_spaceTo.SetPosition(TheScreen::Instance()->GetScreenSize().x / 2.0f, TheScreen::Instance()->GetScreenSize().y - 50.0f);
}

void HighscoreState::Update(float dt)
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	// keys must be pressed and not held down to prevent keys from affecting other states

	// check if want to continue
	if (keys[SDL_SCANCODE_SPACE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_SPACE;
	}

	if (!keys[SDL_SCANCODE_SPACE] && m_keyDown && m_keyPressed == SDL_SCANCODE_SPACE)
	{
		m_keyDown = false;

		EndState * temp = new EndState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;

		m_isAlive = false;
		m_isActive = false;
	}

	if (m_highScoreDisplayMax < (int)m_scores.size())
	{
		int offSetIndex = 0;

		// scroll high score
		if (keys[SDL_SCANCODE_UP] && !m_keyDown)
		{
			m_keyDown = true;
			m_keyPressed = SDL_SCANCODE_UP;
		}

		if (keys[SDL_SCANCODE_DOWN] && !m_keyDown)
		{
			m_keyDown = true;
			m_keyPressed = SDL_SCANCODE_DOWN;
		}

		if (!keys[SDL_SCANCODE_DOWN] && m_keyDown && m_keyPressed == SDL_SCANCODE_DOWN)
		{
			m_keyDown = false;

			offSetIndex--;

			if (m_topIndex + offSetIndex < 0)
			{
				offSetIndex = 0;
			}
		}

		if (!keys[SDL_SCANCODE_UP] && m_keyDown && m_keyPressed == SDL_SCANCODE_UP)
		{
			m_keyDown = false;

			offSetIndex++;

			if (m_bottomIndex + offSetIndex >= (int)m_scores.size())
			{
				offSetIndex = 0;
			}
		}

		m_topIndex += offSetIndex;
		m_bottomIndex += offSetIndex;

		for (auto it = m_scoreDisplay.begin(); it != m_scoreDisplay.end(); it++)
		{
			float newY = (*it)->GetPosition().y - (offSetIndex * (*it)->GetTextSize());
			(*it)->SetPosition((*it)->GetPosition().x, newY);
		}
	}
}

void HighscoreState::Draw()
{
	m_background.Draw();
	
	m_title.Draw();

	if (m_highScoreDisplayMax < (int)m_scores.size())
	{
		for (int i = m_topIndex; i <= m_bottomIndex; i++)
		{
			m_scoreDisplay[i]->Draw();
		}
	}
	else
	{
		for (auto it = m_scoreDisplay.begin(); it != m_scoreDisplay.end(); it++)
		{
			(*it)->Draw();
		}
	}

	m_spaceTo.Draw();
}

void HighscoreState::Unload()
{
	std::cout << "\nUnloading HighscoreState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Unload();

	for (auto it = m_scoreDisplay.begin(); it != m_scoreDisplay.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}	
	}
}
