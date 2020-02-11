#include "Player.h"

//Checking if any of the values changed and call the functions accordingly
void Player::update() {
	if (lData->BossEvent != gameData->BossEvent) {
		updateBossEventChange();
		lData->BossEvent = gameData->BossEvent;
	}

	if (lData->Music != gameData->Music) {
		updateMusicChange();
		lData->Music = gameData->Music;
	}

	if (lData->OptionsOn != gameData->OptionsOn) {
		updateOptionsOnChange();
		lData->OptionsOn = gameData->OptionsOn;
	}

	if (lData->OptionsOff != gameData->OptionsOff) {
		updateOptionsOffChange();
		lData->OptionsOff = gameData->OptionsOff;
	}

	if (lData->XAxis != gameData->XAxis) {
		updateXAxis();
		lData->XAxis = gameData->XAxis;
	}

	if (lData->YAxis != gameData->YAxis) {
		updateYAxis();
		lData->YAxis = gameData->YAxis;
	}

	if (lData->InLevel != gameData->InLevel) {
		updateInLevelChange();
		lData->InLevel = gameData->InLevel;
	}
}

//When the Music is switched off from the Options let the Music Player set the state of Stopped, so the
//stream can be restarted if Player chooses to activate music again
void Player::updateMusicChange() {
	if (!gameData->Music && !gameData->BossEvent)
		Stop();
}

void Player::updateOptionsOffChange() {
	//Making sure that the stream has only been paused instead of stopped to resume
	if (gameData->OptionsOff && musPlayer.getStatus() == musPlayer.Paused)
		Resume();
	//If the stream has been stopped and Music were to be reactivated this will turn it back on
	else if (gameData->InLevel && gameData->OptionsOff && gameData->Music && musPlayer.getStatus() == musPlayer.Stopped)
		Play();
}

//Immediatly pause the stream. In case of a stopped stream nothing will happen!
void Player::updateOptionsOnChange() {
	if (gameData->OptionsOn)
		Pause();
}

void Player::updateInLevelChange() {
	//Is Rayman currently Playable and the following conditions meet?
	if (gameData->InLevel && gameData->Music && !gameData->OptionsOn)
		Play();
	//Else the following could have happened: Rayman died and became unplayable for a brief,
	//a cutscene is playing, Rayman is back on overworld. Fade out the music and stop the stream here to be restarted later!
	else
		Fade();
}

void Player::Play()
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

		//Inject loop attributes from SoundtrackList
		if (soundtrackData->Loop) {
			span.offset = microseconds(soundtrackData->LoopOffset);
			span.length = microseconds(soundtrackData->LoopLength);
			musPlayer.setLoopPoints(span);
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