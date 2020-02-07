#include "Player.h"

//I forgot about that tbh... Had the backthought to pass all data from the Watchdog but
//then I figured it might be more complicated and less efficient having to notify the Observer every cycle
//Also it just might be not? Might work this in the future....
void Player::update(void* param) {
	
}

//When the Music is switched off from the Options let the Music Player set the state of Stopped, so the
//stream can be restarted if Player chooses to activate music again
void Player::updateMusicChange(bool param) {
	if (!param)
		Stop();
}

void Player::updateOptionsOffChange(bool param) {
	//Making sure that the stream has only been paused instead of stopped to resume
	if (param && musPlayer.getStatus() == musPlayer.Paused)
		Resume();
	//If the stream has been stopped and Music were to be reactivated this will turn it back on
	else if (gameData->InLevel && param && gameData->Music && musPlayer.getStatus() == musPlayer.Stopped)
		Play();
}

//Immediatly pause the stream. In case of a stopped stream nothing will happen!
void Player::updateOptionsOnChange(bool param) {
	if (param)
		Pause();
}

void Player::updateInLevelChange(bool param) {
	//Is Rayman currently Playable and the following conditions meet?
	if (param && gameData->OptionsOff && gameData->Music && !gameData->OptionsOn)
		Play();
	//Else the following could have happened: Rayman died and became unplayable for a brief,
	//a cutscene is playing, Rayman is back on overworld. Fade out the music and stop the stream here to be restarted later!
	else
		Fade();
}