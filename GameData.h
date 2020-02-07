#ifndef GAMEDATASTRUCT
#define GAMEDATASTRUCT

#include <string>

//The data Im gathering from Rayman
struct GameData {
    uint16_t XAxis;
    uint16_t YAxis;
    std::string World;
    std::string Level;
    bool BossEvent; //Triggered true if Rayman beated the boss
    bool Music; //If Music has been turned on from the options
    bool OptionsOn; //Triggered if the Options panel is visible
    bool OptionsOff; //Triggered false if player requests for the options panel
    bool InLevel; //Triggers true if Rayman is currently playable
};

#endif // !GAMEDATASTRUCT