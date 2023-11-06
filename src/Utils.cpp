#include "../include/Utils.h"

void Utils::assignCardData(CardData* cData, int id, const std::string &nm, CardType ct, EnergyType et)
{
    cData->set_id(id);
    cData->set_name(nm);
    cData->set_ctype(ct);
    cData->set_etype(et);
}

std::ostream& Utils::operator<<(std::ostream& os, const CardData* cData)
{
    os << "Card Name: " << cData->name() << '\n' <<
          "Card ID: " << cData->id() << '\n' <<
          "Card Type: " << cData->ctype() << '\n' <<
          "Energy Type: " << cData->etype() << "\n\n";

    return os;
}

