#include "hyperlink.h"

CppRtf_Element_Hyperlink::CppRtf_Element_Hyperlink(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_Element(rtf,text,font,parFormat)
{
    this->m_hyperlink = "";
}

void CppRtf_Element_Hyperlink::setHyperlink(string hyperlink)
{
    m_hyperlink = hyperlink;
}

string CppRtf_Element_Hyperlink::getOpeningToken()
{
    return "{\\field {\\\\*\\\\fldinst {HYPERLINK \"" + m_hyperlink + "\"}}{\\fldrslt {";
}

string CppRtf_Element_Hyperlink::getClosingToken()
{
    return "}}}";
}
