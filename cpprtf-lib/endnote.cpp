#include "endnote.h"

CppRtf_Endnote::CppRtf_Endnote(CppRtf *rtf, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat):
    CppRtf_Footnote(rtf,text,font,parFormat)
{
}

string CppRtf_Endnote::getTypeAsRtfCode()
{
    return "\\footnote\\ftnalt";
}
