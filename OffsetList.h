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
			//Ditched the idea of autodetect. End-User might want to have custom values
			{"WorldBase", 0x1AD804},
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

			d = *GetData();
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

//Credits to RayCarrot, PluMGMK
//Other known offsets taken straight from PluMGMK's DOSBox patch:
/*
	case RAY_1_00:
		LOG_MSG("Using Rayman 1.00");
		gRayWorldBase = 0x1AD310;
		gRayLevelOffset = 0x00020;
		gRayInLevelOffset = 0x02228;
		gRayMusOnOffset = 0x02234;
		gRayOptionsOnOffset = 0x174FB;
		gRayOptionsOffOffset = 0x174FD;
		gRayBossEventOffset = 0x02257;
		gRayXOffset = 0x00E5C;
		gRayYOffset = 0x00E60;
		break;
	case RAY_1_10:
		LOG_MSG("Using Rayman 1.10");
		gRayWorldBase = 0x1AD7B4;
		gRayLevelOffset = 0x0001C;
		gRayInLevelOffset = 0x02278;
		gRayMusOnOffset = 0x02232;
		gRayOptionsOnOffset = 0x174E7;
		gRayOptionsOffOffset = 0x174E9;
		gRayBossEventOffset = 0x02256;
		gRayXOffset = 0x00E54;
		gRayYOffset = 0x00E58;
		break;
	case RAY_1_12_0:
		LOG_MSG("Detected Rayman 1.12.0 - starting monitoring");
		gRayWorldBase = 0x1AD804;
		gRayLevelOffset = 0x0001C;
		gRayInLevelOffset = 0x02278;
		gRayMusOnOffset = 0x02232;
		gRayOptionsOnOffset = 0x174E7;
		gRayOptionsOffOffset = 0x174E9;
		gRayBossEventOffset = 0x02256;
		gRayXOffset = 0x00E54;
		gRayYOffset = 0x00E58;
		break;
	case RAY_1_12_1:
		LOG_MSG("Using Rayman 1.12.1");
		gRayWorldBase = 0x1AD814;
		gRayLevelOffset = 0x0001C;
		gRayInLevelOffset = 0x02278;
		gRayMusOnOffset = 0x02232;
		gRayOptionsOnOffset = 0x174E7;
		gRayOptionsOffOffset = 0x174E9;
		gRayBossEventOffset = 0x02256;
		gRayXOffset = 0x00E54;
		gRayYOffset = 0x00E58;
		break;
	case RAY_1_12_2:
		LOG_MSG("Using Rayman 1.12.2");
		gRayWorldBase = 0x1AD5B4;
		gRayLevelOffset = 0x0001C;
		gRayInLevelOffset = 0x02278;
		gRayMusOnOffset = 0x02232;
		gRayOptionsOnOffset = 0x174E7;
		gRayOptionsOffOffset = 0x174E9;
		gRayBossEventOffset = 0x02256;
		gRayXOffset = 0x00E54;
		gRayYOffset = 0x00E58;
		break;
	case RAY_1_20:
		LOG_MSG("Detected Rayman 1.20 - starting monitoring");
		gRayWorldBase = 0x1AE868;
		gRayLevelOffset = 0x00034;
		gRayInLevelOffset = 0x022C0;
		gRayMusOnOffset = 0x02278;
		gRayOptionsOnOffset = 0x17523;
		gRayOptionsOffOffset = 0x17525;
		gRayBossEventOffset = 0x022A0;
		gRayXOffset = 0x00EA0;
		gRayYOffset = 0x00EA4;
		break;
	case RAY_1_21:
		LOG_MSG("Detected Rayman 1.21 - starting monitoring");
		gRayWorldBase = 0x1AE7D8;
		gRayLevelOffset = 0x00034;
		gRayInLevelOffset = 0x022C0;
		gRayMusOnOffset = 0x02278;
		gRayOptionsOnOffset = 0x17523;
		gRayOptionsOffOffset = 0x17525;
		gRayBossEventOffset = 0x022A0;
		gRayXOffset = 0x00EA0;
		gRayYOffset = 0x00EA4;
		break;
	case RAY_1_21_CN:
		LOG_MSG("Using Rayman 1.21 (Chinese)");
		gRayWorldBase = 0x1AE9F0;
		gRayLevelOffset = 0x00034;
		gRayInLevelOffset = 0x022C0;
		gRayMusOnOffset = 0x02278;
		gRayOptionsOnOffset = 0x1752B;
		gRayOptionsOffOffset = 0x1752D;
		gRayBossEventOffset = 0x022A0;
		gRayXOffset = 0x00EA0;
		gRayYOffset = 0x00EA4;
*/

#endif