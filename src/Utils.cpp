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

// Work-around for keeping the message files' locations consistent when project compiled using CMake or clang/g++.
// Finds current working directory and adjusts filepath
std::string Utils::constructFilepath(const std::string& filename)
{
    std::string constructedFp;
    std::string cwd = std::filesystem::current_path().filename();

    if (cwd == BUILD_FOLDER)
        constructedFp = "../" + MSG_FILE_OUTPUT_FOLDER + '/' + filename;
    else if (cwd == PROJECT_ROOT)
        constructedFp = MSG_FILE_OUTPUT_FOLDER + '/' + filename;
    else
        throw std::runtime_error("");

    return constructedFp;
}

