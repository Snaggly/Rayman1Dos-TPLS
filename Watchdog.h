#ifndef WATCHDOG
#define WATCHDOG

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <string>
#include <vector>
#include "GameData.h"
#include "Observer.h"

void registerPlayingState(void* fktPtr);
void registerObserver(Observer*);
bool Watch(uint64_t, GameData*);
bool GlitchMusic(bool);
#endif