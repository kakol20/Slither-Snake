#include "Tools.h"

void CutOut(std::string &word, int start, int length)
{
	word = word.substr(start, length);
}

void AddString(std::string & word, const std::string & toAdd)
{
	word = word + toAdd;
}

void ListString(const std::string & word)
{
	if (word.length() == 0)
	{
		std::cout << "String is empty!\n";
	}
	else
	{
		int count = 1;
		for (auto it = word.begin(); it != word.end(); it++)
		{
			std::cout << "Character #" << count++ << ": " << *it << "\n";
		}

		/*for (size_t i = 0; i < word.length(); i++)
		{
			std::cout << word[i] << "\n";
		}*/

		std::cout << "Size: " << word.length() << "\n";
	}
}

void ParseString(std::vector<std::string> & stringVector, std::string & word, const std::string & splitter)
{

	int count = 0;

	std::string tempWord = word;

	while (tempWord != "" || !tempWord.empty())
	{
		size_t divIndex = tempWord.find(splitter);
		size_t tempSize = tempWord.size();
		std::string tempWord2 = tempWord;

		if (divIndex == std::string::npos)
		{
			stringVector.push_back(tempWord);

			tempWord = "";
		}
		else
		{
			CutOut(tempWord2, 0, (int)divIndex);
			stringVector.push_back(tempWord2);

			CutOut(tempWord, (int)(divIndex + splitter.size()), (int)(tempSize - divIndex + splitter.size()));
		}
	}
}

void RemoveCharacter(std::string & word, const char character)
{
	size_t index = word.find(character);
	if (index != std::string::npos)
	{
		auto it = std::find(word.begin(), word.end(), character);

		word.erase(it);

		index = word.find(character);

		if (index != std::string::npos)
		{
			RemoveCharacter(word, character);
		}
	}
	else
	{
		std::cout << "Character not found\n";
	}

	//system("pause");
}

void ToUpper(std::string & word)
{
	std::transform(word.begin(), word.end(), word.begin(), toupper);
}

void ToLower(std::string & word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
}
