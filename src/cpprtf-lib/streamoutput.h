#ifndef STREAMOUTPUT_H
#define STREAMOUTPUT_H
#include "writer/interface.h"
#include <iostream>
#include <fstream>

//Class for writing the rtf output.
class CppRtf_StreamOutput : public CppRtf_Writer_Interface
{
public:
    CppRtf_StreamOutput();

    //sets filename
    void setFilename(string filename);

    //gets filename
    string getFilename();

    //opens file stream
    void open(OpenMode mode);

    //closes file handler
    void close();

    //writes string to file handler
    void write(string data);

    //gets written content
    string getContent();


private:
    string m_filename; //filename
    fstream m_handle; //handler for stream
};

#endif // STREAMOUTPUT_H



