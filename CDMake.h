#ifndef PROTOBUFTEST2_CDMAKE_H
#define PROTOBUFTEST2_CDMAKE_H
#include "CardData.pb.h"

namespace CDMake
{
    void assignCData(CD::CardData& cData,
                     int id,
                     const std::string& nm,
                     CD::CardData::CardType ct,
                     CD::CardData::EnergyType et);
};


#endif //PROTOBUFTEST2_CDMAKE_H
