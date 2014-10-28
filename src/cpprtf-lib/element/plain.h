#ifndef PLAIN_H
#define PLAIN_H
#include "element.h"

// class for creating elements with plain rtf code.
class CppRtf_Element_Plain : public CppRtf_Element
{
public:
    CppRtf_Element_Plain(CppRtf* rtf, string text,CppRtf_Font* font = 0,CppRtf_ParFormat* parFormat = 0);

protected:
    string getOpeningToken(); // gets opening token
    string getClosingToken(); // gets closing token
};

#endif // PLAIN_H
