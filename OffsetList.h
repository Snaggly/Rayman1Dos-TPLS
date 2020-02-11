#ifndef OFFSETS
#define OFFSETS

#include <fstream>
#include "nlohmann/json.hpp"
#include <filesystem>

using namespace nlohmann;

//This struct contains the neccassairy offsets/addresses
struct Offsets {
	uint32_t CDDA;
	uint32_t WorldBase;
	uint32_t MemoryTest;
	uint32_t Level;
	uint32_t InLevel;
	uint32_t Music;
	uint32_t OptionsOn;
	uint32_t OptionsOff;
	uint32_t BossEvent;
	uint32_t XAxis;
	uint32_t YAxis;
	uint32_t Pointer;
};

class OffsetList {
private:
	Offsets d;
	json j;
	
	//Same as Soundtracklist. Should have made a common Interface..
	void BuildNew(const char* FileName) {
		j = {
			//These are example numbers! Each DOSBox will have its own global address
			{"CDDA", 0x2F7D894},
			{"Pointer", 0x8D8350},

			//These are example numbers. Currently for v1.12
			//Will add the other known offsets for other Rayman versions too later for autodetect
			{"WorldBase", 0x1AD804},
			{"MemoryTest", 0x1AD7BC},
			{"Level", 0x1C},
			{"InLevel", 0x2278},
			{"Music", 0x2232},
			{"OptionsOn", 0x174E7},
			{"OptionsOff", 0x174E9},
			{"BossEvent", 0x2256},
			{"XAxis", 0xE54},
			{"YAxis", 0xE58}
		};

		std::ofstream o(FileName);
		o << std::setw(4) << j << std::endl;

	}

public:
	OffsetList(const char* JSONFile) {

		try {
			std::ifstream file(JSONFile);
			if (!file)
				BuildNew(JSONFile);
			else
				file >> j;
		}
		catch (...) {
			BuildNew(JSONFile);
		}
	}

	Offsets* GetData() {
		try {
			d.Pointer = j["Pointer"].get<uint32_t>();
			d.CDDA = j["CDDA"].get<uint32_t>();
			d.WorldBase = j["WorldBase"].get<uint32_t>();
			d.MemoryTest = j["MemoryTest"].get<uint32_t>();
			d.Level = j["Level"].get<uint32_t>();
			d.InLevel = j["InLevel"].get<uint32_t>();
			d.Music = j["Music"].get<uint32_t>();
			d.OptionsOn = j["OptionsOn"].get<uint32_t>();
			d.OptionsOff = j["OptionsOff"].get<uint32_t>();
			d.BossEvent = j["BossEvent"].get<uint32_t>();
			d.XAxis = j["XAxis"].get<uint32_t>();
			d.YAxis = j["YAxis"].get<uint32_t>();

		}
		catch (...) {
			//Crash the application when nothing can be read. There no point in continuing if unsure where to read
			return nullptr; }

		return &d;
	}
};




#endif