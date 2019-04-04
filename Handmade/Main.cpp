
//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------

#include "Game.h"

#include "MenuState.h"

#include <iostream>

int main(int argc, char* args[])
{

	if (!TheGame::Instance()->Initialise("Slither Snake", 1600, 900))
	{
		return -1;
	}

	MenuState * temp = new MenuState;
	temp->Load();
	TheGame::Instance()->AddState(temp);

	
	while (TheGame::Instance()->Run());

	TheGame::Instance()->Shutdown();


	//system("pause");
	//end application
	return 0;

}