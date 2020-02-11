// TPLSservice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Watchdog.h"
#include "GameData.h"
#include "OffsetList.h"
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
    Offsets* offsetData = (OffsetList("DOSBox-Offsets.json").GetData());
    if (offsetData == nullptr)
        return 2;

    GameData* data = new GameData();
    bgm = new BGMPlayer(data);
    midi = new MidiPlayer(data);

    registerPlayingState(&GetPlayingstates);
    registerObserver(bgm);
    registerObserver(midi);

    if (Watch(offsetData, data))
        return 0;
    return 1;
}