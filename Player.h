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
	virtual bool GetSoundtrack() = 0;
	SoundtrackData* soundtrackData = NULL;
	FileSeekStream seeker;
	GameData* lData = new GameData;

public:
	Player(GameData* data) { gameData = data; }
	GameData* gameData; //Needs a reference to the current game data to make case switches in the functions below

	//Observer functions
	virtual void update();
	virtual void updateMusicChange();
	virtual void updateOptionsOffChange();
	virtual void updateOptionsOnChange();
	virtual void updateInLevelChange();
	virtual void updateBossEventChange();
	virtual void updateXAxis();
	virtual void updateYAxis();

	//Basic functions all players should have! 
	virtual void Play(); //See cpp file..

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