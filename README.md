# ProtoIO
ProtoIO is a cross-platform tool to write a container of protobuf messages to a single delimited file and read them back into a container

The functions writeDelimitedTo() and readDelimitedFrom() are adapted from [Kenton Varda's Protobuf patch submission.](https://stackoverflow.com/questions/2340730/are-there-c-equivalents-for-the-protocol-buffers-delimited-i-o-functions-in-ja/22927149#22927149)
They are used internally by two public-facing functions in the ProtoIO namespace: writeMessagesToFile and readMessagesFromFile

WriteMessagesToFile() and readMessagesFromFile() each take two parameters: a string filename, and a reference to an stl container of Message pointers. 
In the case of readMessages, the container passed in will have the read message data appended to it.
Both functions are templated so that they can work with a wide range of STL containers (those that conform to template <typename, Allocator>). 
Additionally, the macros at the top of ProtoIO.h define the proper includes depending on what system the user is running; The OPEN_WRITE and OPEN_READ function definitions are able to account for the differences in syntax.

The protobuf source code is included inside the "dependencies" folder. The top-level CMakeLists.txt should be able to properly locate the protobuf dependencies. 

Alternatively, one can build the project using clang/g++. This requires the user to already have protobuf installed.

    // (replace /usr/local/lib with your protobuf install path)
    clang++ -std=c++14 -stdlib=libc++ main.cpp src/ProtoIO.cpp src/Utils.cpp dependencies/CardData.pb.cc -L/usr/local/lib -lprotobuf -o ProtoIO
