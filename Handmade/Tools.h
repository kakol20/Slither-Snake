#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

void CutOut(std::string & word, int start, int length);

void AddString(std::string & word, const std::string & toAdd);

void ListString(const std::string & word);

void ParseString(std::vector<std::string> & stringVector, std::string& word, const std::string& splitter);

void RemoveCharacter(std::string &word, const char character);

void ToUpper(std::string &word);

void ToLower(std::string &word);

//void printArray(std::vector<auto> arr);

//void

#endif // !TOOLS_H
