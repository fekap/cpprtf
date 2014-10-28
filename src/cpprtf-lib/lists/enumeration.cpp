#include "enumeration.h"
#include "cpprtf.h"

CppRtf_List_Enumeration::CppRtf_List_Enumeration(CppRtf *rtf, int type, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_List(rtf,type,font,parFormat)
{
    this->initListCharDefinition();

    __name = typeid(this).name();
}

void CppRtf_List_Enumeration::initListCharDefinition()
{
    switch ((EnumerationTypes)m_type) {
        case TYPE_ARROW:
            m_listCharFont = new CppRtf_Font(10, "Wingdings");
            m_listChar = "\\\'d8";
            break;
        case TYPE_CIRCLE:
            m_listCharFont = new CppRtf_Font(10, "Courier New");
            m_listChar = " o";
            break;
        case TYPE_DIAMOND:
            m_listCharFont = new CppRtf_Font(10, "Wingdings");
            m_listChar = " v";
            break;
        case TYPE_SQUARE:
            m_listCharFont = new CppRtf_Font(10, "Wingdings");
            m_listChar = "\\\'a7";
            break;
        // default is bullet
        default:
            m_listCharFont = new CppRtf_Font(10, "Symbol");
            m_listChar = "\\\'B7";
    }

    m_rtf->registerFont(m_listCharFont);
}

string CppRtf_List_Enumeration::getListCharFontIndex()
{
    string fontFamily = m_listCharFont->getFontFamily();
    int index = m_rtf->getFontTable()->getFontIndex(fontFamily);
    return cppstring::numtostr(index);
}

string CppRtf_List_Enumeration::getListCharacter(int number)
{
    (void)number;
    return m_listChar;
}
