#ifndef PROTOBUFTEST2_UTILS_H
#define PROTOBUFTEST2_UTILS_H
#include "defs.h"
#include <ostream>

namespace Utils
{
    void assignCardData(CardData* cData, int id, const std::string& nm, CardType ct, EnergyType et);

    std::ostream& operator<<(std::ostream& os, const CardData* cData);
}


#endif //PROTOBUFTEST2_UTILS_H
