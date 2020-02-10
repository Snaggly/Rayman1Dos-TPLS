// TPLSservice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Watchdog.h"
#include "GameData.h"
#include "BGMPlayer.h"
#include "MidiPlayer.h"

using namespace std;

BGMPlayer* bgm;
MidiPlayer* midi;

bool GetPlayingstates() {
    return bgm->PlayingStatus() + midi->PlayingStatus();
}

int main(int argc, char *argv[])
{
    GameData* data = new GameData();
    bgm = new BGMPlayer(data);
    midi = new MidiPlayer(data);

    registerPlayingState(&GetPlayingstates);
    registerObserver(bgm);
    registerObserver(midi);

    if (Watch(0x8D8350, data))
        return 0;
    return 1;
}