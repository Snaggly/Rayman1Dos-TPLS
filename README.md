# Rayman 1 TPLS

This is the effort in making the original TPLS made in late 2017 and presented in [Rayman Plus](https://raymanpc.com/forum/viewtopic.php?f=89&t=25867) modular and cross platform.

## Compiling
Currently there is no Makefile done. It is written in Visual Studio and can be only compiled within Visual Studio, but I'm looking towards writing one soon. 

It is dependent on [nlohmann-json-v3.7.3](https://github.com/nlohmann/json) for reading the settings and [SFML-2.5.1](https://www.sfml-dev.org/) for audio playback.

## Usage
Easiest way to use TPLS under Windows is to download the latest update for Rayman Plus and launch Rayman from there. Alternatively you can download the latest binary from the releases. Be aware that you'll have to manage the Soundtrack files and the DOSBox pointers on your own. To see how I built the default "Music.dat" file refer to [PackageBuilder.h](https://github.com/Snaggly/Rayman1Dos-TPLS/blob/master/PackageBuilder.h). Each release will be by default bounded to a given DOSBox and Rayman version. See the release notes. To be able to use it under a different DOSBox release you'll have to assign a different Pointer and CDDA address in your DOSBox-Offsets.json file. Finding these can be done with CheatEngine. In the release notes you will also find the information to which Rayman version it is bounded to. To change that you will have to define other offsets in the same file. See [OffsetList.h](https://github.com/Snaggly/Rayman1Dos-TPLS/blob/master/OffsetList.h) in the comments for the known values.

## Examples
***Changing Soundtrack for Level 4***
```json
"RAY4.LEV": {
	"File": "Music.dat",
	"Length": 1164268,
	"Loop": true,
	"LoopLength": 30157278,
	"LoopOffset": 9824853,
	"Offset": 37066076
}
```
to:
```json
"RAY4.LEV": {
	"File": "E:\\MyMusic\\MyBetterMusic.ogg",
	"Length": 5327144,
	"Loop": false,
	"LoopLength": 0,
	"LoopOffset": 0,
	"Offset": 0
}
```
Here I changed the default track, which was in the Music.dat package at an 37066076 offset and having a length of 1164268 to a local file at E:\MyMusic\MyBetterMusic.ogg. Keep in mind since it's local, the starting position/offset of the actual OGG file will be a 0, while the length will be the actual file length in bytes. Since it doesn't have looping attributes, meaning that after a given length in microseconds the soundstream jumps back to a given offset in microseconds, both values can stay at 0 and Loop will can be false. Loop in this scope is just to activate the looping attributes! The track will still loop, but from the beginning!

***Changing Rayman v1.12 to v1.00***
```json
{
    "BossEvent": 8790,
    "CDDA": 49797268,
    "InLevel": 8824,
    "Level": 28,
    "Music": 8754,
    "OptionsOff": 95465,
    "OptionsOn": 95463,
    "Pointer": 9274192,
    "WorldBase": 1759236,
    "XAxis": 3668,
    "YAxis": 3672
}
```
to:
```json
{
    "BossEvent": ‭8791‬,
    "CDDA": 49797268,
    "InLevel": 8744,
    "Level": 32,
    "Music": 8756,
    "OptionsOff": 95485,
    "OptionsOn": 95483‬,
    "Pointer": 9274192,
    "WorldBase": 1757968‬,
    "XAxis": 3676‬,
    "YAxis": 3680‬
}
```
Took the values from [OffsetList.h](https://github.com/Snaggly/Rayman1Dos-TPLS/blob/master/OffsetList.h) . Be aware that they have to be decimal !

## License
[LGPL v3](https://www.gnu.org/licenses/lgpl-3.0.html)