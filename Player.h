#ifndef PLAYER
#define PLAYER

#include "Observer.h"
#include "SoundtrackList.h"
#include "GameData.h"
#include <SFML/Audio.hpp>
#include "FileSeekStream.h"

using namespace sf;
class Player : public Observer
{
private:
	//I honestly don't know. Maybe later.
protected:
	//These should be abstract. The players will handle different tracks!
	Music::Span<Time> span;
	Music musPlayer;
	virtual void Play() = 0;
	virtual bool GetSoundtrack() = 0;
	SoundtrackData* soundtrackData = NULL;
	FileSeekStream seeker;

public:
	Player(GameData* data) { gameData = data; }
	GameData* gameData; //Needs a reference to the current game data to make case switches in the functions below

	//Observer functions
	virtual void update(void* param);
	virtual void updateMusicChange(bool param);
	virtual void updateOptionsOffChange(bool param);
	virtual void updateOptionsOnChange(bool param);
	virtual void updateInLevelChange(bool param);
	virtual void updateBossEventChange(bool param) = 0; //This one is abstract! Players will handle a Boss Event differently!
	

	//Basic functions all players should have! 
	void Pause() {
		musPlayer.pause();
	}

	void Resume() {
		musPlayer.play();
	}

	void Stop() {
		musPlayer.stop();
	}

	void Fade() {
		for (float volume = 100.f; volume > 1.f; --volume) {
			musPlayer.setVolume(volume);
			sleep(milliseconds(5));
		}
		Stop();
		musPlayer.setVolume(100.f);
	}
};

#endif