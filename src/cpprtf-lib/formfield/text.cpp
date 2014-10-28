#include "text.h"

CppRtf_FormField_Text::CppRtf_FormField_Text(CppRtf *rtf, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_FormField(rtf,font,parFormat)
{

}

string CppRtf_FormField_Text::getRtfCode()
{
    return "{\\fftype0\\fftypetxt0{\\\\*\\\\ffname Text1}}";
}

string CppRtf_FormField_Text::getType()
{
    return "FORMTEXT";
}
