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
	void FadeThread() {
		for (float volume = 100.f; volume > 1.f; --volume) {
			musPlayer.setVolume(volume);
			sleep(milliseconds(100));
		}
		Stop();
		musPlayer.setVolume(100.f);
	}

	//I honestly don't know what else. Maybe later.
protected:
	
	Music::Span<Time> span;
	Music musPlayer;
	//This should be abstract. The players will handle different tracks!
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
		std::thread fader([this] {
			for (float volume = 100.f; volume > 1.f; --volume) {
				musPlayer.setVolume(volume);
				sleep(milliseconds(5));
			}
			Stop();
			musPlayer.setVolume(100.f);
		});
		fader.detach(); //So each player doesnt hang one after the other while it's looping...
	}
};

#endif