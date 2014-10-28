#include "tools/stringtools.h"
#include "note.h"
#include "footnote.h"

CppRtf_DocHead_Note::CppRtf_DocHead_Note():
    m_footnoteNumberingType(CppRtf_Footnote::NUMTYPE_ARABIC_NUMBERS),
    m_endnoteNumberingType(CppRtf_Footnote::NUMTYPE_ROMAN_LC),
    m_footnoteRestartEachPage(false),
    m_endnoteRestartEachPage(false),
    m_footnoteStartNumber(1),
    m_endnoteStartNumber(1)
{
}

void CppRtf_DocHead_Note::setFootnoteNumberingType(int numberingType)
{
    m_footnoteNumberingType=numberingType;
}

int CppRtf_DocHead_Note::getFootnoteNumberingType()
{
    return m_footnoteNumberingType;
}

void CppRtf_DocHead_Note::setEndnoteNumberingType(int numberingType)
{
    m_endnoteNumberingType=numberingType;
}

int CppRtf_DocHead_Note::getEndnoteNumberingType()
{
    return m_endnoteNumberingType;
}

void CppRtf_DocHead_Note::setFootnoteStartNumber(int startNumber)
{
    m_footnoteStartNumber=startNumber;
}

int CppRtf_DocHead_Note::getFootnoteStartNumber()
{
    return m_footnoteStartNumber;
}

void CppRtf_DocHead_Note::setEndnoteStartNumber(int startNumber)
{
    m_endnoteStartNumber=startNumber;
}

int CppRtf_DocHead_Note::getEndnoteStartNumber()
{
    return m_endnoteStartNumber;
}

void CppRtf_DocHead_Note::setRestartFootnoteNumberEachPage(bool restart)
{
    m_footnoteRestartEachPage=restart;
}

bool CppRtf_DocHead_Note::isRestartFootnoteNumberEachPage()
{
    return m_footnoteRestartEachPage;
}

void CppRtf_DocHead_Note::setRestartEndnoteNumberEachPage(bool restart)
{
    m_endnoteRestartEachPage=restart;
}

bool CppRtf_DocHead_Note::isRestartEndnoteNumberEachPage()
{
    return m_endnoteRestartEachPage;
}

string CppRtf_DocHead_Note::getNumberingTypeAsRtf(int numbering, string prefix)
{
    switch (numbering) {
    case CppRtf_Footnote::NUMTYPE_ALPHABETH_LC:
        return prefix+"alc";
    case CppRtf_Footnote::NUMTYPE_ALPHABETH_UC:
        return prefix+"auc";
    case CppRtf_Footnote::NUMTYPE_ROMAN_LC:
        return prefix+"rlc";
    case CppRtf_Footnote::NUMTYPE_ROMAN_UC:
        return prefix+"ruc";
    case CppRtf_Footnote::NUMTYPE_CHICAGO:
        return prefix+"chi";
    case CppRtf_Footnote::NUMTYPE_KOREAN_1:
        return prefix+"chosung";
    case CppRtf_Footnote::NUMTYPE_KOREAN_2:
        return prefix+"ganada";
    case CppRtf_Footnote::NUMTYPE_CIRCLE:
        return prefix+"cnum";
    case CppRtf_Footnote::NUMTYPE_KANJI_1:
        return prefix+"dbnum";
    case CppRtf_Footnote::NUMTYPE_KANJI_2:
        return prefix+"dbnumd";
    case CppRtf_Footnote::NUMTYPE_KANJI_3:
        return prefix+"dbnumt";
    case CppRtf_Footnote::NUMTYPE_KANJI_4:
        return prefix+"dbnumk";
    case CppRtf_Footnote::NUMTYPE_DOUBLE_BYTE:
        return prefix+"dbchar";
    case CppRtf_Footnote::NUMTYPE_CHINESE_1:
        return prefix+"gbnum";
    case CppRtf_Footnote::NUMTYPE_CHINESE_2:
        return prefix+"gbnumd";
    case CppRtf_Footnote::NUMTYPE_CHINESE_3:
        return prefix+"gbnuml";
    case CppRtf_Footnote::NUMTYPE_CHINESE_4:
        return prefix+"gbnumk";
    case CppRtf_Footnote::NUMTYPE_CHINESE_ZODIAC_1:
        return prefix+"zodiac";
    case CppRtf_Footnote::NUMTYPE_CHINESE_ZODIAC_2:
        return prefix+"zodiacd";
    case CppRtf_Footnote::NUMTYPE_CHINESE_ZODIAC_3:
        return prefix+"zodiacl";
    default:
        // const name NUMTYPE_ARABIC_NUMBERS
        return prefix+"ar";
    }
}

string CppRtf_DocHead_Note::getContent()
{
    string content = CppRtf_DocHead_Note::getNumberingTypeAsRtf(m_footnoteNumberingType) +" "+
                     CppRtf_DocHead_Note::getNumberingTypeAsRtf(m_endnoteNumberingType, "\\aftnn")+" "+
                     "\\ftnstart" + cppstring::numtostr(m_footnoteStartNumber) + " " +
                     "\\aftnstart" + cppstring::numtostr(m_endnoteStartNumber) + " ";

    if (m_footnoteRestartEachPage) {
        content += "\\ftnrstpg ";
    }
    if (m_endnoteRestartEachPage) {
        content += "\\aftnrstpg ";
    }

    return content;
}
