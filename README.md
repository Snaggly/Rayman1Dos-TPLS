# Rayman 1 TPLS

This is the effort in making the original TPLS made in late 2017 and presented in [Rayman Plus](https://raymanpc.com/forum/viewtopic.php?f=89&t=25867) modular and cross platform.

## Compiling
Currently there is no Makefile done. It is written in Visual Studio and can be only compiled within Visual Studio, but I'm looking towards writing one soon. 

It is dependent on [nlohmann-json-v3.7.3](https://github.com/nlohmann/json) for reading the settings and [SFML-2.5.1](https://www.sfml-dev.org/) for audio playback.

## Usage
Prerequisites is that the given audio tracks from Rayman have to be muted or disabled. The soundtrack will play on top of DOSBox! Easiest way to do this is replace the audio tracks with a abrupt silenced tone.

Start the executable with the correct settings after DOSBox has loaded Rayman and enjoy!