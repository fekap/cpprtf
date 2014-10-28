#include "plain.h"

CppRtf_Element_Plain::CppRtf_Element_Plain(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_Element(rtf,text,font,parFormat)
{
    this->setIsRtfCode();
}

string CppRtf_Element_Plain::getOpeningToken()
{
    return "";
}

string CppRtf_Element_Plain::getClosingToken()
{
    return "";
}
