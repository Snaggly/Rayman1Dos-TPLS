#ifndef OBSERVER
#define OBSERVER

//Trying to translate the Event System in C# by utilizing an Observable Pattern
class Observer
{
public:
	virtual void update() = 0;
};

#endif