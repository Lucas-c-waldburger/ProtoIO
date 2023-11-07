#include <iostream>
#include <vector>
#include "include/ProtoIO.h"
#include "include/Utils.h"

// TO COMPILE: (clang or g++)
    // clang++ -std=c++14 -stdlib=libc++ main.cpp src/ProtoIO.cpp src/Utils.cpp dependencies/CardData.pb.cc -L/usr/local/lib -lprotobuf -o ProtoIO
// TO RUN:
    // ./ProtoIO

const std::string FILE_NAME = "VecTest.txt";

int main()
{
    using namespace Utils;

    const std::string FILE_PATH = "MsgFileOutput/VecTest.txt";

    //// WRITING FROM CONTAINER TO FILE

    CardData* c1 = new CardData(), * c2 = new CardData(), * c3 = new CardData();

    assignCardData(c1, 1, "Charmander", CardType::CardData_CardType_CT_PKMN, EnergyType::CardData_EnergyType_ET_FIRE);
    assignCardData(c2, 2, "Squirtle", CardType::CardData_CardType_CT_PKMN, EnergyType::CardData_EnergyType_ET_WATER);
    assignCardData(c3, 3, "Pikachu", CardType::CardData_CardType_CT_PKMN, EnergyType::CardData_EnergyType_ET_ELECTRIC);

    std::vector<CardData*> cdMessages = {c1, c2, c3};

    ProtoIO::writeMessagesToFile(FILE_PATH, cdMessages);

    for (auto& msg : cdMessages)
        delete msg;

    cdMessages.clear();


    //// READING FROM FILE TO CONTAINER

    ProtoIO::readMessagesFromFile(FILE_PATH, cdMessages);

    for (auto& msg : cdMessages)
    {
        std::cout << msg;
        delete msg;
    }

    return 0;
}
