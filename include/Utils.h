#ifndef PROTOBUFTEST2_UTILS_H
#define PROTOBUFTEST2_UTILS_H
#include "defs.h"
#include <ostream>
#include <filesystem>

const std::string BUILD_FOLDER = "build";
const std::string PROJECT_ROOT = "ProtoIO";
const std::string MSG_FILE_OUTPUT_FOLDER = "MsgFileOutput";

namespace Utils
{
    void assignCardData(CardData* cData, int id, const std::string& nm, CardType ct, EnergyType et);

    std::ostream& operator<<(std::ostream& os, const CardData* cData);

    std::string constructFilepath(const std::string& filename);
}


#endif //PROTOBUFTEST2_UTILS_H
