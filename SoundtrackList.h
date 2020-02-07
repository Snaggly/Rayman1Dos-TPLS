#ifndef SOUNDTRACKLIST
#define SOUNDTRACKLIST

#include <fstream>
#include "nlohmann/json.hpp"
#include <filesystem>

using namespace nlohmann;

struct SoundtrackData {
	std::string FileName = std::string();
	int64_t Offset = 0;
	int64_t Length = 0;
	int64_t LoopOffset = 0;
	int64_t LoopLength = 0;
	bool Loop = false;
};

class SoundtrackList {
private:
	SoundtrackData d;
	json j;
	const char* Mode;
	void BuildNew(const char* FileName) {
		j = {
			{"BGM", {
				{"RAY1.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 6551897},
						{"Length", 2486607},
						{"LoopOffset", 19784580},
						{"LoopLength", 49655420},
						{"Loop", true}
					}},
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 0},
						{"Length", 2165079},
						{"LoopOffset", 13543628},
						{"LoopLength", 50000184},
						{"Loop", true}
					}},
					{"RAY3.LEV", {
						{"File", "Music.dat"},
						{"Offset", 99121549},
						{"Length", 2587734},
						{"LoopOffset", 19870590},
						{"LoopLength", 39182972},
						{"Loop", true}
					}},
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 4338453},
						{"Length", 2213444},
						{"LoopOffset", 16437006},
						{"LoopLength", 46153652},
						{"Loop", true}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 6551897},
						{"Length", 2486607},
						{"LoopOffset", 19784580},
						{"LoopLength", 49655420},
						{"Loop", true}
					}},
					{"RAY8.LEV", {
						{"File", "Music.dat"},
						{"Offset", 99121549},
						{"Length", 2587734},
						{"LoopOffset", 19870590},
						{"LoopLength", 39182972},
						{"Loop", true}
					}},
					{"RAY10.LEV", {
						{"File", "Music.dat"},
						{"Offset", 4338453},
						{"Length", 2213444},
						{"LoopOffset", 16437006},
						{"LoopLength", 46153652},
						{"Loop", true}
					}},
					{"RAY11.LEV", {
						{"File", "Music.dat"},
						{"Offset", 4338453},
						{"Length", 2213444},
						{"LoopOffset", 16437006},
						{"LoopLength", 46153652},
						{"Loop", true}
					}},
					{"RAY12.LEV", {
						{"File", "Music.dat"},
						{"Offset", 6551897},
						{"Length", 2486607},
						{"LoopOffset", 19784580},
						{"LoopLength", 49655420},
						{"Loop", true}
					}},
					{"RAY13.LEV", {
						{"File", "Music.dat"},
						{"Offset", 0},
						{"Length", 2165079},
						{"LoopOffset", 13543628},
						{"LoopLength", 50000184},
						{"Loop", true}
					}},
					{"RAY14.LEV", {
						{"File", "Music.dat"},
						{"Offset", 47942616},
						{"Length", 2034721},
						{"LoopOffset", 13170431},
						{"LoopLength", 53802904},
						{"Loop", true}
					}},
					{"RAY15.LEV", {
						{"File", "Music.dat"},
						{"Offset", 9038504},
						{"Length", 2315595},
						{"LoopOffset", 11518957},
						{"LoopLength", 53801044},
						{"Loop", true}
					}},
					{"RAY16.LEV", {
						{"File", "Music.dat"},
						{"Offset", 11354099},
						{"Length", 1979343},
						{"LoopOffset", 6155170},
						{"LoopLength", 50511496},
						{"Loop", true}
					}},
					{ "RAY17.LEV", {
						{"File", "Music.dat"},
						{"Offset", 99121549},
						{"Length", 2587734},
						{"LoopOffset", 19870590},
						{"LoopLength", 39182972},
						{"Loop", true}
					}},
					{ "RAY18.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{ "RAY19.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{ "RAY20.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{ "RAY21.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{ "RAY22.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY2.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 27319852},
						{"Length", 2440268},
						{"LoopOffset", 13271996},
						{"LoopLength", 56950224},
						{"Loop", true}
					}},
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 23011790},
						{"Length", 2371596},
						{"LoopOffset", 15176893},
						{"LoopLength", 48118048},
						{"Loop", true}
					}},
					{"RAY3.LEV", {
						{"File", "Music.dat"},
						{"Offset", 18383028},
						{"Length", 2406299},
						{"LoopOffset", 18932268},
						{"LoopLength", 52495780},
						{"Loop", true}
					}},
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 37066076},
						{"Length", 1164268},
						{"LoopOffset", 9824853},
						{"LoopLength", 30157278},
						{"Loop", true}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 23011790},
						{"Length", 2371596},
						{"LoopOffset", 15176893},
						{"LoopLength", 48118048},
						{"Loop", true}
					}},
					{"RAY6.LEV", {
						{"File", "Music.dat"},
						{"Offset", 33846724},
						{"Length", 1735157},
						{"LoopOffset", 22594444},
						{"LoopLength", 34285556},
						{"Loop", true}
					}},
					{"RAY7.LEV", {
						{"File", "Music.dat"},
						{"Offset", 35581881},
						{"Length", 1484195},
						{"LoopOffset", 13922948},
						{"LoopLength", 39410384},
						{"Loop", true}
					}},
					{"RAY8.LEV", {
						{"File", "Music.dat"},
						{"Offset", 27319852},
						{"Length", 2440268},
						{"LoopOffset", 13271996},
						{"LoopLength", 56950224},
						{"Loop", true}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 35581881},
						{"Length", 1484195},
						{"LoopOffset", 13922948},
						{"LoopLength", 39410384},
						{"Loop", true}
					}},
					{"RAY10.LEV", {
						{"File", "Music.dat"},
						{"Offset", 20789327},
						{"Length", 2222463},
						{"LoopOffset", 7764081},
						{"LoopLength", 50075920},
						{"Loop", true}
					}},
					{"RAY11.LEV", {
						{"File", "Music.dat"},
						{"Offset", 99121549},
						{"Length", 2587734},
						{"LoopOffset", 19870590},
						{"LoopLength", 39182972},
						{"Loop", true}
					}},
					{"RAY12.LEV", {
						{"File", "Music.dat"},
						{"Offset", 25383386},
						{"Length", 1936466},
						{"LoopOffset", 23303334},
						{"LoopLength", 40976848},
						{"Loop", true}
					}},
					{"RAY13.LEV", {
						{"File", "Music.dat"},
						{"Offset", 29760120},
						{"Length", 1977001},
						{"LoopOffset", 35877460},
						{"LoopLength", 40985536},
						{"Loop", true}
					}},
					{"RAY14.LEV", {
						{"File", "Music.dat"},
						{"Offset", 20789327},
						{"Length", 2222463},
						{"LoopOffset", 7764081},
						{"LoopLength", 50075920},
						{"Loop", true}
					}},
					{"RAY15.LEV", {
						{"File", "Music.dat"},
						{"Offset", 31737121},
						{"Length", 2109603},
						{"LoopOffset", 17879386},
						{"LoopLength", 48000612},
						{"Loop", true}
					}},
					{"RAY16.LEV", {
						{"File", "Music.dat"},
						{"Offset", 31737121},
						{"Length", 2109603},
						{"LoopOffset", 17879386},
						{"LoopLength", 48000612},
						{"Loop", true}
					}},
					{"RAY17.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY18.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY3.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 44428810},
						{"Length", 1134385},
						{"LoopOffset", 8875487},
						{"LoopLength", 48001180},
						{"Loop", true}
					}},
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 44428810},
						{"Length", 1134385},
						{"LoopOffset", 8875487},
						{"LoopLength", 48001180},
						{"Loop", true}
					}},
					{"RAY3.LEV", {
						{"File", "Music.dat"},
						{"Offset", 38230344},
						{"Length", 2582952},
						{"LoopOffset", 15040749},
						{"LoopLength", 55997892},
						{"Loop", true}
					}},
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 45563195},
						{"Length", 2379421},
						{"LoopOffset", 20560046},
						{"LoopLength", 47213288},
						{"Loop", true}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 44428810},
						{"Length", 1134385},
						{"LoopOffset", 8875487},
						{"LoopLength", 48001180},
						{"Loop", true}
					}},
					{"RAY6.LEV", {
						{"File", "Music.dat"},
						{"Offset", 44428810},
						{"Length", 1134385},
						{"LoopOffset", 8875487},
						{"LoopLength", 48001180},
						{"Loop", true}
					}},
					{"RAY7.LEV", {
						{"File", "Music.dat"},
						{"Offset", 47942616},
						{"Length", 2034721},
						{"LoopOffset", 13170431},
						{"LoopLength", 53802904},
						{"Loop", true}
					}},
					{"RAY8.LEV", {
						{"File", "Music.dat"},
						{"Offset", 13333442},
						{"Length", 2908519},
						{"LoopOffset", 24935942},
						{"LoopLength", 69866096},
						{"Loop", true}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 49977337},
						{"Length", 1233841},
						{"LoopOffset", 7192154},
						{"LoopLength", 30470588},
						{"Loop", true}
					}},
					{"RAY10.LEV", {
						{"File", "Music.dat"},
						{"Offset", 42404362},
						{"Length", 2024448},
						{"LoopOffset", 38592904},
						{"LoopLength", 33345554},
						{"Loop", true}
					}},
					{"RAY11.LEV", {
						{"File", "Music.dat"},
						{"Offset", 99121549},
						{"Length", 2587734},
						{"LoopOffset", 19870590},
						{"LoopLength", 39182972},
						{"Loop", true}
					}},
					{"RAY12.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY13.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY4.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 53346060},
						{"Length", 1538246},
						{"LoopOffset", 7567165},
						{"LoopLength", 43913492},
						{"Loop", true}
					}},
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 57616420},
						{"Length", 2302096},
						{"LoopOffset", 19988436},
						{"LoopLength", 49471836},
						{"Loop", true}
					}},
					{"RAY3.LEV", {
						{"File", "Music.dat"},
						{"Offset", 51211178},
						{"Length", 2134882},
						{"LoopOffset", 17803242},
						{"LoopLength", 46828956},
						{"Loop", true}
					}},
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 59918516},
						{"Length", 2409369},
						{"LoopOffset", 8702630},
						{"LoopLength", 63090952},
						{"Loop", true}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 57616420},
						{"Length", 2302096},
						{"LoopOffset", 19988436},
						{"LoopLength", 49471836},
						{"Loop", true}
					}},
					{"RAY6.LEV", {
						{"File", "Music.dat"},
						{"Offset", 57616420},
						{"Length", 2302096},
						{"LoopOffset", 19988436},
						{"LoopLength", 49471836},
						{"Loop", true}
					}},
					{"RAY7.LEV", {
						{"File", "Music.dat"},
						{"Offset", 54884306},
						{"Length", 2732114},
						{"LoopOffset", 11134467},
						{"LoopLength", 62898480},
						{"Loop", true}
					}},
					{"RAY8.LEV", {
						{"File", "Music.dat"},
						{"Offset", 54884306},
						{"Length", 2732114},
						{"LoopOffset", 11134467},
						{"LoopLength", 62898480},
						{"Loop", true}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 37066076},
						{"Length", 1164268},
						{"LoopOffset", 9824853},
						{"LoopLength", 30157278},
						{"Loop", true}
					}},
					{"RAY10.LEV", {
						{"File", "Music.dat"},
						{"Offset", 47942616},
						{"Length", 2034721},
						{"LoopOffset", 13170431},
						{"LoopLength", 53802904},
						{"Loop", true}
					}},
					{"RAY11.LEV", {
						{"File", "Music.dat"},
						{"Offset", 62327885},
						{"Length", 2492390},
						{"LoopOffset", 13614241},
						{"LoopLength", 52252428},
						{"Loop", true}
					}},
					{"RAY12.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY13.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
			}},
				{"RAY5.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 67145488},
						{"Length", 2517043},
						{"LoopOffset", 7526757},
						{"LoopLength", 56618728},
						{"Loop", true}
					}},
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 76854486},
						{"Length", 2109335},
						{"LoopOffset", 14753696},
						{"LoopLength", 49410224},
						{"Loop", true}
					}},
					{"RAY3.LEV", {
						{"File", "Music.dat"},
						{"Offset", 72015734},
						{"Length", 2595378},
						{"LoopOffset", 11992449},
						{"LoopLength", 52590952},
						{"Loop", true}
					}},
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 74611112},
						{"Length", 2243374},
						{"LoopOffset", 4161406},
						{"LoopLength", 41665080},
						{"Loop", true}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 67145488},
						{"Length", 2517043},
						{"LoopOffset", 7526757},
						{"LoopLength", 56618728},
						{"Loop", true}
					}},
					{"RAY6.LEV", {
						{"File", "Music.dat"},
						{"Offset", 74611112},
						{"Length", 2243374},
						{"LoopOffset", 4161406},
						{"LoopLength", 41665080},
						{"Loop", true}
					}},
					{"RAY7.LEV", {
						{"File", "Music.dat"},
						{"Offset", 76854486},
						{"Length", 2109335},
						{"LoopOffset", 14753696},
						{"LoopLength", 49410224},
						{"Loop", true}
					}},
					{"RAY8.LEV", {
						{"File", "Music.dat"},
						{"Offset", 72015734},
						{"Length", 2595378},
						{"LoopOffset", 11992449},
						{"LoopLength", 52590952},
						{"Loop", true}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 64820275},
						{"Length", 2325213},
						{"LoopOffset", 20417460},
						{"LoopLength", 50004672},
						{"Loop", true}
					}},
					{"RAY10.LEV", {
						{"File", "Music.dat"},
						{"Offset", 69662531},
						{"Length", 2353203},
						{"LoopOffset", 14772154},
						{"LoopLength", 49227844},
						{"Loop", true}
					}},
					{"RAY11.LEV", {
						{"File", "Music.dat"},
						{"Offset", 69662531},
						{"Length", 2353203},
						{"LoopOffset", 14772154},
						{"LoopLength", 49227844},
						{"Loop", true}
					}},
					{"RAY12.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY13.LEV", {
						{"File", "Music.dat"},
						{"Offset", 101709283},
						{"Length", 1370316},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY6.WLD", {
			{"RAY1.LEV", {
				{"File", "Music.dat"},
				{"Offset", 82491087},
				{"Length", 2115990},
				{"LoopOffset", 20277552},
				{"LoopLength", 43454560},
				{"Loop", true}
			}},
			{"RAY2.LEV", {
				{"File", "Music.dat"},
				{"Offset", 81165011},
				{"Length", 1326076},
				{"LoopOffset", 8510023},
				{"LoopLength", 29968072},
				{"Loop", true}
			}},
			{"RAY3.LEV", {
				{"File", "Music.dat"},
				{"Offset", 78963821},
				{"Length", 2201190},
				{"LoopOffset", 3270090},
				{"LoopLength", 57856012},
				{"Loop", true}
			}},
			{"RAY4.LEV", {
				{"File", "Music.dat"},
				{"Offset", 84607077},
				{"Length", 2516946},
				{"LoopOffset", 11462721},
				{"LoopLength", 56393516},
				{"Loop", true}
			}}
		}}
			}},
			{"Midi", {
				{"RAY1.WLD", {
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 93746215},
						{"Length", 1661628},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"Victory", {
						{"File", "Music.dat"},
						{"Offset", 98888779},
						{"Length", 232770},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY2.WLD", {
					{"RAY4.LEV", {
						{"File", "Music.dat"},
						{"Offset", 89595654},
						{"Length", 634589},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY3.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 96201425},
						{"Length", 1569546},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY5.LEV", {
						{"File", "Music.dat"},
						{"Offset", 96201425},
						{"Length", 1569546},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 96201425},
						{"Length", 1569546},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY4.WLD", {
					{"RAY1.LEV", {
						{"File", "Music.dat"},
						{"Offset", 98128931},
						{"Length", 759848},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY9.LEV", {
						{"File", "Music.dat"},
						{"Offset", 98128931},
						{"Length", 759848},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY5.WLD", {
					{"RAY6.LEV", {
						{"File", "Music.dat"},
						{"Offset", 91112299},
						{"Length", 1816842},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}},
				{"RAY6.WLD", {
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 87956163},
						{"Length", 1639491},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}}
			}},
			{"Pos", {
				{"RAY1.WLD", {
					{"RAY6.LEV1", {
						{"File", "Music.dat"},
						{"Offset", 0},
						{"Length", 2165079},
						{"LoopOffset", 13543628},
						{"LoopLength", 50000184},
						{"Loop", true}
					}},
					{"RAY6.LEV2", {
						{"File", "Music.dat"},
						{"Offset", 2165079},
						{"Length", 2173374},
						{"LoopOffset", 32759456},
						{"LoopLength", 39636508},
						{"Loop", true}
					}},
					{"RAY7.LEV1", {
						{"File", "Music.dat"},
						{"Offset", 9038504},
						{"Length", 2315595},
						{"LoopOffset", 11518957},
						{"LoopLength", 53801044},
						{"Loop", true}
					}},
					{"RAY7.LEV2", {
						{"File", "Music.dat"},
						{"Offset", 103079599},
						{"Length", 494418},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}},
					{"RAY9.LEV1", {
						{"File", "Music.dat"},
						{"Offset", 0},
						{"Length", 2165079},
						{"LoopOffset", 13543628},
						{"LoopLength", 50000184},
						{"Loop", true}
					}},
					{"RAY9.LEV2", {
						{"File", "Music.dat"},
						{"Offset", 16241961},
						{"Length", 2141067},
						{"LoopOffset", 23649818},
						{"LoopLength", 53753492},
						{"Loop", true}
					}}
				}},
				{"RAY3.WLD", {
					{"RAY2.LEV", {
						{"File", "Music.dat"},
						{"Offset", 97770971},
						{"Length", 184365},
						{"LoopOffset", 0},
						{"LoopLength", 0},
						{"Loop", false}
					}}
				}}
			}},
		};

		std::ofstream o(FileName);
		o << std::setw(4) << j << std::endl;

	}

public:
	SoundtrackList(const char* Mode, const char* JSONFile) {
		this->Mode = Mode;

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

	SoundtrackData* GetData(std::string World, std::string Level) {
		try {
			auto& jMWL = j[Mode][World][Level];
			d.FileName = jMWL["File"].get<std::string>();
			d.Offset = jMWL["Offset"].get<int64_t>();
			d.Length = jMWL["Length"].get<int64_t>();
			d.LoopOffset = jMWL["LoopOffset"].get<int64_t>();
			d.LoopLength = jMWL["LoopLength"].get<int64_t>();
			d.Loop = jMWL["Loop"].get<bool>();

		}
		catch (json::exception) {
			d.FileName = "";
			d.Offset = 0;
			d.Length = 0;
			d.LoopOffset = 0;
			d.LoopLength = 0;
			d.Loop = false;
		}
		
		return &d;
	}
};

#endif