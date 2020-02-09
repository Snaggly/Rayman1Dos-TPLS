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
	
	//This should get and play new tracks when Rayman is in the desired position in the level
	void updateXAxis() override;
	void updateYAxis() override;
};

#endif