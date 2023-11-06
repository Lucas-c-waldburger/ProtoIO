#ifndef PROTOBUFTEST2_PROTOIO_H
#define PROTOBUFTEST2_PROTOIO_H

#include <iostream>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <fcntl.h>
#include <cerrno>
#include "../dependencies/CardData.pb.h"


// Check if running Mac/Linux or Windows, include the correct headers for io operations
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>

#define OPEN_READ(filename) (open(filename.c_str(), O_RDONLY))
#define OPEN_WRITE(filename) (open(filename.c_str(), O_WRONLY | O_CREAT | S_IWUSR, 0666)) // 0666 sets read + write permissions when file created
#define CLOSE_FILE(fd) (close(fd))

#else
#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>

#define OPEN_READ(filename) (_open(filename.c_str(), _O_RDONLY))
#define OPEN_WRITE(filename) (_open(filename.c_str(), _O_CREAT | _O_WRONLY | _S_IWRITE))
#define CLOSE_FILE(fd) (_close(fd))
#endif


namespace ProtoIO
{
    bool writeDelimitedTo(google::protobuf::Message* message,
                          google::protobuf::io::ZeroCopyOutputStream* rawOutput);

    bool readDelimitedFrom(google::protobuf::io::ZeroCopyInputStream* rawInput,
                           google::protobuf::Message* message, bool* cleanEOF);

    bool writeSingleMessageToFile(const std::string& filename, google::protobuf::Message* msg);

    bool readSingleMessageFromFile(const std::string& filename, google::protobuf::Message* msg);

    template <typename T, template <typename U, typename = std::allocator<U>> class MsgContainer>
    bool writeMessagesToFile(const std::string& filename, MsgContainer<T*>& messages);

    template<typename T, template <typename U, typename = std::allocator<U>> class MsgContainer>
    bool readMessagesFromFile(const std::string& filename, MsgContainer<T*>& messages);
}


// takes a reference to a non-associative stl container of Message pointers and writes to file
template <typename T, template <typename U, typename = std::allocator<U>> class MsgContainer>
bool ProtoIO::writeMessagesToFile(const std::string& filename, MsgContainer<T*>& messages)
{
    int outFd = OPEN_WRITE(filename);

    if (outFd == -1)
    {
        perror("Error opening file for write");
        return false;
    }

    google::protobuf::io::ZeroCopyOutputStream* rawOutput = new google::protobuf::io::FileOutputStream(outFd);

    bool success = true;
    for (const auto& msg : messages)
    {
        if (!writeDelimitedTo(msg, rawOutput))
        {
            std::cout << "Error serializing with cached sizes";
            success = false;
            break;
        }
    }

    delete rawOutput;
    CLOSE_FILE(outFd);

    return success;
}

// takes a reference to a non-associative stl container of Message pointers and populates it from delimited file
template<typename T, template <typename U, typename = std::allocator<U>> class MsgContainer>
bool ProtoIO::readMessagesFromFile(const std::string& filename, MsgContainer<T*>& messages)
{
    int inFd = OPEN_READ(filename);

    if (inFd == -1)
    {
        perror("Error opening file for read");
        return false;
    }

    google::protobuf::io::ZeroCopyInputStream* rawInput = new google::protobuf::io::FileInputStream(inFd);

    bool cleanEOF = false, success = true;
    while (!cleanEOF)
    {
        T* nextMsg = new T;

        if (!readDelimitedFrom(rawInput, nextMsg, &cleanEOF)) // no more messages to read or other error
        {
            delete nextMsg;

            if (!cleanEOF) // check if readDelimited exited from reading all messages or from an error
            {
                std::cout << "Protobuf reader terminated before end of file";
                success = false;
            }
        }
        else
        {
            messages.push_back(nextMsg);
        }
    }

    delete rawInput;
    CLOSE_FILE(inFd);

    return success;
}


#endif //PROTOBUFTEST2_PROTOIO_H
