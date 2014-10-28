#include "dropdown.h"
#include "utf8.h"
#include "cpprtf.h"

CppRtf_FormField_Dropdown::CppRtf_FormField_Dropdown(CppRtf *rtf, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_FormField(rtf,font,parFormat)
{

}

void CppRtf_FormField_Dropdown::addItem(string text)
{
    m_items.push_back(text);
}

void CppRtf_FormField_Dropdown::setItems(vector<string> items)
{
    m_items = items;
}

string CppRtf_FormField_Dropdown::getRtfCode()
{
    string content = "{\\fftype2\\ffres25\\fftypetxt0\\ffhaslistbox\\ffdefres0";
    for(vector<string>::iterator it = m_items.begin();it != m_items.end();it++){
        string text = *it;
        text = CppRtf_Utf8::getUnicodeEntities(text,m_rtf->getCharset());
        content += "{\\\\*\\\\ffl " + text +"}";
    }
    content += "}";
    return content;
}

string CppRtf_FormField_Dropdown::getType()
{
    return "FORMDROPDOWN";
}
