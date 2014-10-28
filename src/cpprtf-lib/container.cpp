#include "container.h"

CppRtf_Container::CppRtf_Container(CppRtf* rtf):CppRtf_Container_Base(rtf)
{
}

CppRtf_Footnote *CppRtf_Container::addFootnote(string noteText, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_Footnote* footnote = new CppRtf_Footnote(m_rtf, noteText, font, parFormat);
    addElement(footnote);
    return footnote;
}

CppRtf_Endnote *CppRtf_Container::addEndnoot(string noteText, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_Endnote* endnote = new CppRtf_Endnote(m_rtf, noteText, font, parFormat);
    addElement(endnote);
    return endnote;
}

void CppRtf_Container::addList(CppRtf_List *list)
{
    addElement(list);
}

void CppRtf_Container::addEnumeration(CppRtf_List_Enumeration *enumeration)
{
    addElement(enumeration);
}

void CppRtf_Container::addNumbering(CppRtf_List_Numbering *numbering)
{
    addElement(numbering);
}

CppRtf_FormField_Checkbox *CppRtf_Container::addCheckbox(CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_FormField_Checkbox *checkBox = new CppRtf_FormField_Checkbox(m_rtf, font, parFormat);
    addElement(checkBox);
    return checkBox;
}

CppRtf_FormField_Dropdown *CppRtf_Container::addDropdown(CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_FormField_Dropdown* dropdown = new CppRtf_FormField_Dropdown(m_rtf, font, parFormat);
    addElement(dropdown);
    return dropdown;
}

CppRtf_FormField_Text *CppRtf_Container::addText(CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_FormField_Text* textField = new CppRtf_FormField_Text(m_rtf, font, parFormat);
    addElement(textField);
    return textField;
}
