#include "BGMPlayer.h"

//Background Music handler
SoundtrackList sl("BGM", "SoundtrackList.json");
SoundtrackList slPos("Pos", "SoundtrackList.json");

bool BGMPlayer::GetSoundtrack()
{
	if (xsection + ysection)
		soundtrackData = slPos.GetData(gameData->World.c_str(), (gameData->Level + std::to_string(xsection + ysection)).c_str());
	else
		soundtrackData = sl.GetData(gameData->World.c_str(), gameData->Level.c_str());
	return soundtrackData->FileName != "";
}

void BGMPlayer::updateXAxis()
{
	//Flight with Mosquito Level
	if (gameData->World == "RAY1.WLD" && gameData->Level == "RAY7.LEV") {
		//Phase when Bzzit behaves like a friend
		if ((gameData->XAxis < 4850 || gameData->XAxis > 9250) && xsection != 1) {
			xsection = 1;
			updateInLevelChange(); //Final checks before letting the track play
		}
		//Phase when Bzzit tries to kill Rayman again
		else if (gameData->XAxis > 4850 && gameData->XAxis < 9250 && xsection != 2) {
			xsection = 2;
			updateInLevelChange();
		}
	}
	else {
		xsection = 0;
	}
}

void BGMPlayer::updateYAxis()
{
	if (gameData->World == "RAY1.WLD") {
		//Bzzit attacks level
		if (gameData->Level == "RAY6.LEV") {
			//Phase were Rayman tries to commit suicide by jumping into the abyss
			if (gameData->YAxis < 830 && ysection != 1) {
				ysection = 1;
				updateInLevelChange();
			}
			//Phase were Bzzit tries to help Rayman in getting killed
			else if (gameData->YAxis > 830 && ysection != 2) {
				ysection = 2;
				updateInLevelChange();
			}
		}
		//Tarayzan level
		else if (gameData->Level == "RAY9.LEV") {
			//Phase were Rayman helps Tarayzan getting dressed
			if (gameData->YAxis > 2650 && ysection != 1) {
				ysection = 1;
				updateInLevelChange();
			}
			//Phase were Tarayzan showing his gratitude by letting Rayman getting drown
			else if (gameData->YAxis < 2650 && ysection != 2) {
				ysection = 2;
				updateInLevelChange();
			}
		}
		else {
			ysection = 0;
		}
	}
}
