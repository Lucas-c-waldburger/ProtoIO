#include <iostream>
#include "ProtoIO.h"
#include "CDMake.h"


// TO COMPILE:
    // clang++ -std=c++11 -stdlib=libc++ main.cpp ProtoIO.cpp CDMake.cpp CardData.pb.cc -L/usr/local/lib -lprotobuf -o main

int main()
{
    auto cd1 = new CD::CardData();
//    CDMake::assignCData(*cd1, 1, "Charmander", CD::CardData_CardType_CT_PKMN, CD::CardData_EnergyType_ET_FIRE);

    std::cout << std::boolalpha << ProtoIO::readCDFromFile("test.txt", *cd1);

    std::cout << '\n' << cd1->name();

    delete cd1;

    return 0;
}
