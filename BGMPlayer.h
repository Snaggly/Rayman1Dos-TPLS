#ifndef BGMPLAYER
#define BGMPLAYER

#include "Player.h"
class BGMPlayer :
	public Player
{
protected: 
	bool GetSoundtrack();

public:
	BGMPlayer(GameData* data) : Player(data){}
};

#endif