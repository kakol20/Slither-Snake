
//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------

#include "Game.h"

int main(int argc, char* args[])
{

	if (!TheGame::Instance()->Initialise("Slither Snake", 1600, 900))
	{
		return -1;
	}
	
	while (TheGame::Instance()->Run());

	TheGame::Instance()->Shutdown();

	//end application
	return 0;

}