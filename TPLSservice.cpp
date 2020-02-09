// TPLSservice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Watchdog.h"
#include "GameData.h"
#include "BGMPlayer.h"
#include "MidiPlayer.h"
#include "PosPlayer.h"

using namespace std;

int main(int argc, char *argv[])
{
    GameData* data = new GameData();
    BGMPlayer* bgm = new BGMPlayer(data);
    MidiPlayer* midi = new MidiPlayer(data);
    PosPlayer* pos = new PosPlayer(data);

    registerObserver(bgm);
    registerObserver(midi);
    registerObserver(pos);

    if (Watch(0x8D8350, data))
        return 0;
    return 1;
}