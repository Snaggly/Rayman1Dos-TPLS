#ifndef BGMPLAYER
#define BGMPLAYER

#include "Player.h"
class BGMPlayer :
	public Player
{
protected: 
	void Play();
	bool GetSoundtrack();

public:
	BGMPlayer(GameData* data) : Player(data){}

	virtual void updateBossEventChange(bool param);
};

#endif