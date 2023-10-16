#include "ProtoIO.h"

// Check if on UNIX or POSIX system, include the correct headers for io operations
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    #include <unistd.h>

    #define OPEN_READ(filename) (open(filename.c_str(), O_RDONLY))
    #define OPEN_WRITE(filename) (open(filename.c_str(), O_WRONLY | O_CREAT | S_IWUSR))
    #define CLOSE_FILE(fd) (close(fd))
#else
    #include <io.h>
    #include <sys\stat.h>
    #include <sys\types.h>

    #define OPEN_READ(filename) (_open(filename.c_str(), _O_RDONLY))
    #define OPEN_WRITE(filename) (_open(filename.c_str(), _O_CREAT | _O_WRONLY | _S_IWRITE))
    #define CLOSE_FILE(fd) (_close(fd))
#endif


bool ProtoIO::writeDelimitedTo(const google::protobuf::Message& message,
                               google::protobuf::io::ZeroCopyOutputStream* rawOutput)
{
    // We create a new coded stream for each message.  Don't worry, this is fast.
    google::protobuf::io::CodedOutputStream output(rawOutput);

    // Write the size.
    const int size = message.ByteSizeLong();
    output.WriteVarint32(size);

    uint8_t* buffer = output.GetDirectBufferForNBytesAndAdvance(size);
    if (buffer != NULL)
    {
        // Optimization:  The message fits in one buffer, so use the faster
        // direct-to-array serialization path.
        message.SerializeWithCachedSizesToArray(buffer);
    }

    else
    {
        // Slightly-slower path when the message is multiple buffers.
        message.SerializeWithCachedSizes(&output);
        if (output.HadError())
        return false;
    }

    return true;
}


bool ProtoIO::readDelimitedFrom(google::protobuf::io::ZeroCopyInputStream* rawInput,
                                google::protobuf::Message* message, bool* clean_eof)
{
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    google::protobuf::io::CodedInputStream input(rawInput);
    const int start = input.CurrentPosition();
    if (clean_eof)
    *clean_eof = false;


    // Read the size.
    uint32_t size;
    if (!input.ReadVarint32(&size))
    {
        if (clean_eof)
            *clean_eof = (input.CurrentPosition() == start);
        return false;
    }
    // Tell the stream not to read beyond that size.
    google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);

    // Parse the message.
    if (!message->MergeFromCodedStream(&input))
        return false;
    if (!input.ConsumedEntireMessage())
        return false;

    // Release the limit.
    input.PopLimit(limit);

    return true;
}

bool ProtoIO::writeCDToFile(const std::string &filename, const google::protobuf::Message& msg)
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

bool ProtoIO::readCDFromFile(const std::string& filename, google::protobuf::Message& msg)
{
    int inFd = OPEN_READ(filename);

    if (inFd == -1)
    {
        perror("Error opening file for read");
        return false;
    }

    google::protobuf::io::ZeroCopyInputStream* input = new google::protobuf::io::FileInputStream(inFd);

    bool cleanEOF = false;
    bool success = readDelimitedFrom(input, &msg, &cleanEOF);

    delete input;
    CLOSE_FILE(inFd);

    return success;
}

