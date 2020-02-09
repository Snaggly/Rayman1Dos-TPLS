#include "MidiPlayer.h"

//Handling of the Midi tracks
SoundtrackList slMidi("Midi", "SoundtrackList.json");


bool MidiPlayer::GetSoundtrack()
{
	//Getting the soundtracks. Each player should get its own!
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