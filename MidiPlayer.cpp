#include "MidiPlayer.h"

//Handling of the Midi tracks
SoundtrackList slMidi("Midi", "SoundtrackList.json");

//Unsure if I put this into the Player to reduce clutter. No significant change from BGM Player
void MidiPlayer::Play()
{
	try {
		//Before start playing a new track, I need to make sure there is a track to play
		if (!GetSoundtrack())
			return;
		Stop();

		//This will fail in case the soundtrackData is a nullptr! Making sure above line catches before I come here
		if (soundtrackData->FileName == "")
			return;

		//Getting the subtrack from the container as a sub filestream
		seeker.setData(soundtrackData->FileName.c_str(), soundtrackData->Offset, soundtrackData->Length);

		//Loading the stream into SMFL's music player
		if (!musPlayer.openFromStream(seeker)) {
			return;
		}

		//Start playing it if everything checked out above
		musPlayer.setLoop(true);
		musPlayer.play();
	}
	catch (...) {
		//Just in case, so the program doesn just crash. Needs proper error handling!
		return;
	}
}

bool MidiPlayer::GetSoundtrack()
{
	//Getting the soundtracks. Each player should get its own!
	soundtrackData = slMidi.GetData(gameData->World.c_str(), gameData->Level.c_str());
	return soundtrackData->FileName != "";
}

void MidiPlayer::updateBossEventChange(bool param) {
	//Handle the victory jingle when defeating a boss!
	if (param) {
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
	else {
		Stop();
	}
}