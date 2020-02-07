#include "BGMPlayer.h"

//Background Music handler
SoundtrackList sl("BGM", "SoundtrackList.json");

//Again, I should look up to have this in the abstract class
void BGMPlayer::Play()
{
	try {
		//Look up MidiPlayer.cpp
		if (!GetSoundtrack())
			return;
		Stop();
		if (soundtrackData->FileName == "")
			return;
		seeker.setData(soundtrackData->FileName.c_str(), soundtrackData->Offset, soundtrackData->Length);
		if (!musPlayer.openFromStream(seeker)) {
			return;
		}

		span.offset = microseconds(soundtrackData->LoopOffset);
		span.length = microseconds(soundtrackData->LoopLength);

		if (soundtrackData->Loop)
			musPlayer.setLoopPoints(span);
		musPlayer.setLoop(true);
		musPlayer.play();
	}
	catch (...) {
		return;
	}
}

bool BGMPlayer::GetSoundtrack()
{
	soundtrackData = sl.GetData(gameData->World.c_str(), gameData->Level.c_str());
	return soundtrackData->FileName != "";
}

void BGMPlayer::updateBossEventChange(bool param) {
	//Just stop the track if boss battle is won, to let Midi handle the funny jingle
	if (param)
		Fade();
}
