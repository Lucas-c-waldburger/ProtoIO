#include "CDMake.h"

void CDMake::assignCData(CD::CardData &cData, int id, const std::string &nm, CD::CardData::CardType ct,
                         CD::CardData::EnergyType et)
{
    cData.set_id(id);
    cData.set_name(nm);
    cData.set_ctype(ct);
    cData.set_etype(et);
}

