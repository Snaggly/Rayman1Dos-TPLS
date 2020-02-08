#include "PosPlayer.h"

//Copy-Pasted mostly from BGMPlayer
SoundtrackList slPos("Pos", "SoundtrackList.json");
char section = 0; //To get the correct soundtrack of the given phase, but also to check if not already is playing it

bool PosPlayer::GetSoundtrack()
{
	soundtrackData = slPos.GetData(gameData->World.c_str(), (gameData->Level + std::to_string(section)).c_str());
	return soundtrackData->FileName != "";
}

void PosPlayer::updateXAxis()
{
	//Flight with Mosquito Level
	if (gameData->World == "RAY1.WLD" && gameData->Level == "RAY7.LEV") {
		//Phase when Bzzit behaves like a friend
		if ((gameData->XAxis < 4850 || gameData->XAxis > 9250) && section != 1) {
			section = 1;
			updateInLevelChange(); //Final checks before letting the track play
		}
		//Phase when Bzzit tries to kill Rayman again
		else if (gameData->XAxis > 4850 && gameData->XAxis < 9250 && section != 2) {
			section = 2;
			updateInLevelChange();
		}
	}
	//Mr Stones Chase Level
	else if (gameData->World == "RAY3.WLD" && gameData->Level == "RAY2.LEV") {
		//Phase where Mr Stones tries to crush Rayman
		if (((1930 < gameData->XAxis && gameData->XAxis < 4525) || (5670 < gameData->XAxis && gameData->XAxis < 6670))) {
			if (section != 1) {
				section = 1;
				updateInLevelChange();
			}
		}
		else if(section != 0) {
			section = 0; //Reset the section if not being chased anymore!
			Stop();
		}
	}
}

void PosPlayer::updateYAxis()
{
	if (gameData->World == "RAY1.WLD") {
		//Bzzit attacks level
		if(gameData->Level == "RAY6.LEV") {
			//Phase were Rayman tries to commit suicide by jumping into the abyss
			if (gameData->YAxis < 830 && section != 1) {
				section = 1;
				updateInLevelChange();
			}
			//Phase were Bzzit tries to help Rayman in getting killed
			else if (gameData->YAxis > 830 && section != 2) {
				section = 2;
				updateInLevelChange();
			}
		}
		//Tarayzan level
		else if (gameData->Level == "RAY9.LEV") {
			//Phase were Rayman helps Tarayzan getting dressed
			if (gameData->YAxis > 2650 && section != 1) {
				section = 1;
				updateInLevelChange();
			}
			//Phase were Tarayzan showing his gratitude by letting Rayman getting drown
			else if (gameData->YAxis < 2650 && section != 2) {
				section = 2;
				updateInLevelChange();
			}
		}
	}
}
