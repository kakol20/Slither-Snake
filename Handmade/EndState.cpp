#include "EndState.h"

#include "Game.h"

EndState::EndState()
{
	m_previousState = nullptr;
	m_keyDown = false;

	m_keyPressed = 0;

	m_finalScore = 0;
}

EndState::EndState(GameState* prevState)
{
	m_previousState = prevState;
	m_keyDown = false;

	m_keyPressed = 0;

	m_finalScore = 0;

	if (dynamic_cast<PlayState*>(prevState))
	{
		m_finalScore = dynamic_cast<PlayState*>(prevState)->GetScore();
		m_finalTimeScore = dynamic_cast<PlayState*>(prevState)->GetTimeScore();
	}

	m_timeElapsed = prevState->GetTimeElapsed();
}


EndState::~EndState()
{
}

void EndState::Load()
{
	std::cout << "\nLoading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;

	m_background.Load("Assets/Textures/End.png", "END_BG", 1600, 900);
	m_background.SetVisible(true);

	m_isAlive = true;
	m_isActive = true;

	m_finalScoreDisplay.SetFont("INTRO_FONT");
	m_finalScoreDisplay.SetColor(255, 255, 255);
	std::string finalScoreText = "Final Score: " + std::to_string(m_finalScore);
	m_finalScoreDisplay.SetSize(25 * finalScoreText.size(), 50);
	m_finalScoreDisplay.SetText(finalScoreText);
}

void EndState::Update(float dt)
{
	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_SPACE] && !m_keyDown) // to avoid key holding effecting the next game state
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_SPACE;
	}
	else if (keys[SDL_SCANCODE_ESCAPE] && !m_keyDown)
	{
		m_keyDown = true;
		m_keyPressed = SDL_SCANCODE_ESCAPE;
	}

	if (!keys[SDL_SCANCODE_SPACE] && m_keyDown && m_keyPressed == SDL_SCANCODE_SPACE) // go to the menu when space bar pressed
	{
		MenuState* temp = new MenuState(this);
		temp->Load();

		TheGame::Instance()->ChangeState(temp);

		temp = nullptr;
		m_isAlive = false;
		m_isActive = false;

		m_keyDown = false;
	}
	else if (!keys[SDL_SCANCODE_ESCAPE] && m_keyDown && m_keyPressed == SDL_SCANCODE_ESCAPE) // exit game
	{
		m_isAlive = false;
		m_isActive = false;

		std::fstream file;

		file.open("Data/GameRunning.txt", std::ios_base::in);

		// Checks if the file exists
		if (!file.is_open())
		{
			file.close();
			file.open("Data/GameRunning.txt", std::ios_base::out);

			file << "       GAME RUNNING TIME\n";
			file << "-------------------------------\n";
		}

		// OUTPUTTING TIME SPENT ON GAME
		file.close();
		file.open("Data/GameRunning.txt", std::ios_base::app);
		std::string output = "Time Spent On Game: " + std::to_string(m_timeElapsed / 1000.0f) + " seconds\n";
		file << output;
		file.close();

		// SAVING HIGHSCORE IN A BINARY FILE
		// First binary data stores the number of players that have played the game
		file.open("Data/score.dat", std::ios_base::in | std::ios_base::binary);

		int totalPlayers = 0;
		if (!file.is_open()) // check if file exists or not
		{
			file.close();
			file.open("Data/score.dat", std::ios_base::out | std::ios_base::binary);

			file.write((char*)&totalPlayers, sizeof(int));

			file.close();
			file.open("Data/score.dat", std::ios_base::in | std::ios_base::binary);
		}

		file.read((char*)&totalPlayers, sizeof(int)); // checks for the number of players that have played the game

		std::deque<HighScore> scoreArray; // puts players in a vector to be sorted later

		for (int i = 0; i < totalPlayers; i++) // goes through the players saved in binary file
		{
			HighScore temp;

			file.read((char*)&temp, sizeof(HighScore));

			scoreArray.push_back(temp);
		}

		file.close();
		
		totalPlayers++;

		HighScore newScore;
		newScore.score = m_finalScore;
		newScore.playerID = totalPlayers;
		newScore.timeSpent = m_finalTimeScore;

		scoreArray.push_back(newScore);

		std::sort(scoreArray.begin(), scoreArray.end(), SortScores);

		// Saves sorted scores
		file.open("Data/score.dat", std::ios_base::out | std::ios_base::binary);

		file.write((char*)&totalPlayers, sizeof(int));

		for (size_t i = 0; i < scoreArray.size(); i++)
		{
			file.write((char*)&(scoreArray[i]), sizeof(HighScore));
		}

		file.close();
	}

	m_timeElapsed += dt;
}

void EndState::Draw()
{
	m_background.Draw();

	m_finalScoreDisplay.Draw(50, 50);
}

void EndState::Unload()
{
	std::cout << "\nUnloading EndState\n";
	std::cout << "---------------------------------------------------------------" << std::endl;
	m_background.Unload();
}
