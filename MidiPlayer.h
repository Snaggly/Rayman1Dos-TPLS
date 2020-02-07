#ifndef MidiPLAYER
#define MidiPLAYER

#include "Player.h"
class MidiPlayer :
	public Player
{
protected:
	void Play();
	bool GetSoundtrack();

public:
	MidiPlayer(GameData* data) : Player(data) {}
	virtual void updateBossEventChange(bool param);
};

#endif