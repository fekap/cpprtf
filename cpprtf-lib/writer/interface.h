#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
//#include "global.h"

using namespace std;

// Interface for writing the rtf output.

class CppRtf_Writer_Interface
{
public:

    enum OpenMode{
        ReadOnly,
        WriteOnly
    };

    // opens handle
    virtual void open(OpenMode mode) = 0;

    // close handle
    virtual void close() = 0;

    // writes data
    virtual void write(string data) = 0;

    //gets written content
    virtual string getContent() = 0;
};

#endif // INTERFACE_H
