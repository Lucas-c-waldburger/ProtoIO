#include "../include/ProtoIO.h"

bool ProtoIO::writeDelimitedTo(google::protobuf::Message* message,
                               google::protobuf::io::ZeroCopyOutputStream* rawOutput)
{
    google::protobuf::io::CodedOutputStream output(rawOutput);

    // find size of msg in bytes & write to ostream
    const int size = message->ByteSizeLong();
    output.WriteVarint32(size);

    // null if enough space for msg in buffer, else gets ptr advanced over "size" bites
    uint8_t* buffer = output.GetDirectBufferForNBytesAndAdvance(size);

    if (buffer)
    {
        // message will fit in one buffer
        message->SerializeWithCachedSizesToArray(buffer);
    }
    else
    {
        // message needs multiple buffers
        message->SerializeWithCachedSizes(&output);

        if (output.HadError())
            return false;
    }

    return true;
}


bool ProtoIO::readDelimitedFrom(google::protobuf::io::ZeroCopyInputStream* rawInput,
                                google::protobuf::Message* message, bool* cleanEOF)
{
    google::protobuf::io::CodedInputStream input(rawInput);
    const int start = input.CurrentPosition();

    if (cleanEOF)
        *cleanEOF = false;

    // get size of msg from the varint
    uint32_t size;
    if (!input.ReadVarint32(&size))
    {
        if (cleanEOF)
            *cleanEOF = (input.CurrentPosition() == start);
        return false;
    }

    // set read limit to the msg size
    google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);

    // parse msg
    if (!message->MergeFromCodedStream(&input))
        return false;
    if (!input.ConsumedEntireMessage())
        return false;

    // remove limit for next read operation
    input.PopLimit(limit);

    return true;
}

bool ProtoIO::writeSingleMessageToFile(const std::string& filename, google::protobuf::Message* msg)
{
    int outFd = OPEN_WRITE(filename);

    if (outFd == -1)
    {
        perror("Error opening file for write");
        return false;
    }

    google::protobuf::io::ZeroCopyOutputStream* output = new google::protobuf::io::FileOutputStream(outFd);

    bool success = writeDelimitedTo(msg, output);

    delete output;
    CLOSE_FILE(outFd);

    return success;
}

bool ProtoIO::readSingleMessageFromFile(const std::string& filename, google::protobuf::Message* msg)
{
    int inFd = OPEN_READ(filename);

    if (inFd == -1)
    {
        perror("Error opening file for read");
        return false;
    }

    google::protobuf::io::ZeroCopyInputStream* input = new google::protobuf::io::FileInputStream(inFd);

    bool cleanEOF = false, success = true;
    if (!readDelimitedFrom(input, msg, &cleanEOF) && !cleanEOF)
    {
        std::cout << "Error occurred while reading message file";
        success = false;
    }

    delete input;
    CLOSE_FILE(inFd);

    return success;
}


