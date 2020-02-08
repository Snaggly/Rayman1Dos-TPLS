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

void registerObserver(Observer*);
void Watch(uint64_t, GameData*);
bool GlitchMusic(bool);
#endif