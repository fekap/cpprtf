#ifndef HYPERLINK_H
#define HYPERLINK_H
#include "element.h"

//class for creating hyperlink elements
class CppRtf_Element_Hyperlink : public CppRtf_Element
{
public:
    CppRtf_Element_Hyperlink(CppRtf* rtf, string text, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);
    void setHyperlink(string hyperlink); //sets hyperling

protected:
    string m_hyperlink;
    string getOpeningToken(); // gets opening token
    string getClosingToken(); // gets closing token
};

#endif // HYPERLINK_H
