#ifndef STRING_H
#define STRING_H
#include "interface.h"

class CppRtf_Writer_String : public CppRtf_Writer_Interface
{
public:
    CppRtf_Writer_String();
    // opens handle
    virtual void open();

    // close handle
    virtual void close();

    /*
         * write content - internal use
         * NOTE: Re-opens the handle if it's closed and empties content.
         *       May be not the best behavior, yet, but it is as it is.
         *       It is used for PHPRtfLite's output generation. */
    virtual void write(string data);

    //gets written content
    virtual string getContent();
private:
    bool m_closed; //falg, true if handle is closed
    string m_content; //content
};

#endif // STRING_H
