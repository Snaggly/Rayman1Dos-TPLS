#ifndef MidiPLAYER
#define MidiPLAYER

#include "Player.h"
class MidiPlayer :
	public Player
{
protected:
	bool GetSoundtrack();

public:
	MidiPlayer(GameData* data) : Player(data) {}
	void updateBossEventChange();
	void updateXAxis();
	void updateYAxis();
	void updateWorldLoading();
};

#endif