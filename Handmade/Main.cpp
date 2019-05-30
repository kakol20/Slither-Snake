
//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------

#include "Game.h"

#include "MenuState.h"

#include <iostream>

int main(int argc, char* args[])
{

	if (!TheGame::Instance()->Initialise("Data/Game.ini"))
	{
		return -1;
	}

	MenuState * temp = new MenuState;
	temp->Load();
	TheGame::Instance()->AddState(temp);

	temp = nullptr;
	while (TheGame::Instance()->Run());

	TheGame::Instance()->Shutdown();


	//system("pause");
	//end application
	return 0;

}