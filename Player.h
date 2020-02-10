#ifndef PLAYER
#define PLAYER

#include "Observer.h"
#include "SoundtrackList.h"
#include "GameData.h"
#include <SFML/Audio.hpp>
#include "FileSeekStream.h"
#include <thread>

using namespace sf;
class Player : public Observer
{
private:
	//To prevent two faders overlapping
	bool IsFading = false;

protected:
	Music::Span<Time> span;
	Music musPlayer;
	//This should be abstract. The players will handle different tracks!
	virtual bool GetSoundtrack() = 0; 
	SoundtrackData* soundtrackData = NULL;
	FileSeekStream seeker;
	GameData* lData = new GameData;
	char xsection = 0;
	char ysection = 0;

public:
	Player(GameData* data) { gameData = data; }
	GameData* gameData; //Needs a reference to the current game data to make case switches in the functions below

	//Observer functions
	virtual void update();
	virtual void updateMusicChange();
	virtual void updateOptionsOffChange();
	virtual void updateOptionsOnChange();
	virtual void updateInLevelChange();
	virtual void updateBossEventChange() = 0;
	virtual void updateXAxis() = 0;
	virtual void updateYAxis() = 0;
	virtual void updateWorldLoading() = 0;

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
		if (!IsFading) {
			IsFading = true;
			std::thread fader([this] {
				for (float volume = 100.f; volume > 1.f; --volume) {
					musPlayer.setVolume(volume);
					sleep(milliseconds(5));
				}
				Stop();
				musPlayer.setVolume(100.f);
				IsFading = false;
				});
			fader.detach(); //So each player doesnt hang one after the other while it's looping...
		}
		
	}
};

#endif