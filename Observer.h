#ifndef OBSERVER
#define OBSERVER

//Trying to translate the Event System in C# by utilizing an Observable Pattern
class Observer
{
public:
	//Passing each gamedata to the observers when the Watchdog detects changes
	virtual void updateMusicChange(bool param) = 0;

	virtual void updateOptionsOffChange(bool param) = 0;

	virtual void updateOptionsOnChange(bool param) = 0;

	virtual void updateInLevelChange(bool param) = 0;

	virtual void updateBossEventChange(bool param) = 0;
};

#endif