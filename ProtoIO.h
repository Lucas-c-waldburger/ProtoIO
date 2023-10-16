
#ifndef PROTOBUFTEST2_PROTOIO_H
#define PROTOBUFTEST2_PROTOIO_H
#include <iostream>
#include "CardData.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <fcntl.h>

#include <cerrno>



namespace ProtoIO
{



//#include <io.h>
//#include <fcntl.h>



    bool writeDelimitedTo(const google::protobuf::Message& message,
                          google::protobuf::io::ZeroCopyOutputStream* rawOutput);


    bool readDelimitedFrom(google::protobuf::io::ZeroCopyInputStream* rawInput,
                           google::protobuf::Message* message, bool* clean_eof);




    bool writeCDToFile(const std::string& filename, const google::protobuf::Message& msg);

    bool readCDFromFile(const std::string& filename, google::protobuf::Message& msg);


//    int main(int argc, char* argv[])
//    {
//        using CardType = CD::CardData::CardType;
//        using EnergyType = CD::CardData::EnergyType;
//
//        CD::CardData* c1 = new CD::CardData(), * c2 = new CD::CardData();
//        assignCData(*c1, 1, "Charmander", CardType::CardData_CardType_CT_PKMN, EnergyType::CardData_EnergyType_ET_FIRE);
//        assignCData(*c2, 2, "Bulbasaur", CardType::CardData_CardType_CT_PKMN, EnergyType::CardData_EnergyType_ET_GRASS);
//
//
//        const char* filename = "test.txt";
//
//        int outfd = _open(filename, _O_CREAT | _O_WRONLY | _S_IWRITE);
//
//        if (outfd == -1)
//        {
//            std::cout << "File could not be opened";
//            return -1;
//        }
//        google::protobuf::io::ZeroCopyOutputStream* output = new google::protobuf::io::FileOutputStream(outfd);
//        std::cout << std::boolalpha << writeDelimitedTo(*c1, output);
//        std::cout << std::boolalpha << writeDelimitedTo(*c2, output);
//
//
//        delete c1;
//        delete c2;
//        delete output;
//        _close(outfd);
//
//
//
//
//
//
//        return 0;
//    }

};


#endif //PROTOBUFTEST2_PROTOIO_H
