#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <SFML\Audio.hpp>

namespace fs = std::filesystem;

//Here I built my "Music.dat". Basically I just copied the files on top of each other and noted down where I can refind them
void Build(std::string path) {
    std::ofstream output;
    std::ifstream input;
    std::fstream datasheet;
    std::string filename;
    datasheet.open("Datas.txt", std::ios::out);
    datasheet << "Filename" << "\t" << "Offset" << "\t" << "Length"
        << "\t" << "LoopOffset" << "\t" << "LoopLength" << std::endl;
    int64_t size = 0;
    int64_t LoopStart = 0;
    int64_t LoopLength = 0;
    output.open("Music.dat", std::ios::out | std::ios::binary);
    for (const auto& entry : fs::directory_iterator(path)) {
        if (!entry.file_size())
            continue;
        std::cout << entry.path() << std::endl;
        filename = fs::path(entry).filename().string();
        sf::Music player;
        player.openFromFile(path + "\\Loops\\" + filename.substr(0, filename.size() - 4) + "-01.ogg");
        LoopStart = player.getDuration().asMicroseconds();
        player.openFromFile(path + "\\Loops\\" + filename.substr(0, filename.size() - 4) + "-02.ogg");
        LoopLength = player.getDuration().asMicroseconds();
        datasheet << fs::path(entry).filename() << "\t" << size << "\t" << entry.file_size() <<
            "\t" << LoopStart << "\t" << LoopLength << std::endl;
        input.open(entry.path(), std::ios::in | std::ios::binary);
        output << input.rdbuf();
        size += entry.file_size();
        input.close();
    }
    output.close();
    datasheet.close();
}