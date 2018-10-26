#include "ApplicationManager.h"
int main()
	{
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	mciSendString("open music.mp3 type mpegvideo", NULL, 0, NULL);
	mciSendString("play music.mp3 repeat", NULL, 0, NULL);
	do
	{
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);
	return 0;
}

