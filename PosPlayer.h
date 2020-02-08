#ifndef POSPLAYER
#define POSPLAYER

#include "Player.h"
class PosPlayer :
	public Player
{
protected:
	bool GetSoundtrack();

public:
	PosPlayer(GameData* data) : Player(data) {}

	void updateXAxis() override; //This should get and play new tracks when Rayman is in the desired position in the level
	void updateYAxis() override;
};

#endif