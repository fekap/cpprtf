#include "checkbox.h"

CppRtf_FormField_Checkbox::CppRtf_FormField_Checkbox(CppRtf *rtf, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_FormField(rtf,font,parFormat)
{
    m_checked = false;
    m_size = 20;
}

void CppRtf_FormField_Checkbox::setChecked()
{
    m_checked = true;
}

void CppRtf_FormField_Checkbox::setDefaultValue(bool value)
{
    m_checked = value;
}

void CppRtf_FormField_Checkbox::setSize(int size)
{
    m_size = size > 0 ? size : 20;
}

string CppRtf_FormField_Checkbox::getType()
{
    return "FORMCHECKBOX";
}

string CppRtf_FormField_Checkbox::getRtfCode()
{
    return "{\\fftype1\\ffres25\\ffhps" + cppstring::numtostr(m_size) + "\\ffdefres" + (m_checked ? "1" : "0") + "}";
}
