#include "MidiPlayer.h"

//Handling of the Midi tracks
SoundtrackList slMidi("Midi", "SoundtrackList.json");
SoundtrackList slMidiPos("Pos", "SoundtrackList.json");

bool MidiPlayer::GetSoundtrack()
{
	if (xsection)
		soundtrackData = slMidiPos.GetData(gameData->World.c_str(), (gameData->Level + std::to_string(xsection)).c_str());
	else
		soundtrackData = slMidi.GetData(gameData->World.c_str(), gameData->Level.c_str());
	return soundtrackData->FileName != "";
}

void MidiPlayer::updateBossEventChange(){
	//Handle the victory jingle when defeating a boss!
	if (gameData->BossEvent) {
		soundtrackData = slMidi.GetData("RAY1.WLD", "Victory");

		//Repeating the Play() code... Needs some cleanup.
		if (soundtrackData->FileName == "")
			return;

		seeker.setData(soundtrackData->FileName.c_str(), soundtrackData->Offset, soundtrackData->Length);
		if (!musPlayer.openFromStream(seeker)) {
			return;
		}
		musPlayer.setLoop(true);
		musPlayer.play();
	}
}

void MidiPlayer::updateXAxis()
{
	//Mr Stones Chase Level
	if (gameData->World == "RAY3.WLD" && gameData->Level == "RAY2.LEV") {
		//Phase where Mr Stones tries to crush Rayman
		if (((1930 < gameData->XAxis && gameData->XAxis < 4525) || (5670 < gameData->XAxis && gameData->XAxis < 6670))) {
			if (xsection != 1) {
				xsection = 1;
				updateInLevelChange();
			}
		}
		else if (xsection != 0) {
			xsection = 0; //Reset the section if not being chased anymore!
			Stop();
		}
	}
	else {
		xsection = 0;
	}
}

void MidiPlayer::updateYAxis()
{
}

void MidiPlayer::updateWorldLoading()
{
	if (gameData->WorldLoading) {
		soundtrackData = slMidi.GetData("RAY1.WLD", "Loading");

		//Repeating the Play() code... Needs some cleanup.
		if (soundtrackData->FileName == "")
			return;

		seeker.setData(soundtrackData->FileName.c_str(), soundtrackData->Offset, soundtrackData->Length);
		if (!musPlayer.openFromStream(seeker)) {
			return;
		}
		musPlayer.setLoop(true);
		musPlayer.play();
	}
	else {
		Fade();
	}
}