#include "BGMPlayer.h"

//Background Music handler
SoundtrackList sl("BGM", "SoundtrackList.json");

bool BGMPlayer::GetSoundtrack()
{
	soundtrackData = sl.GetData(gameData->World.c_str(), gameData->Level.c_str());
	return soundtrackData->FileName != "";
}
