#include "numbering.h"
#include "tools/stringtools.h"
#include "font.h"
#include "cpprtf.h"

CppRtf_List_Numbering::CppRtf_List_Numbering(CppRtf *rtf, int type, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
    :CppRtf_List(rtf,type,font,parFormat)
{
    m_prefix = "";
    m_suffix = ".";
    m_separator = ".";
    __name = typeid(this).name(); //instanceOf; TODO
}

CppRtf_List_Numbering *CppRtf_List_Numbering::setPrefix(string prefix)
{
    m_prefix = prefix;
    return this;
}

CppRtf_List_Numbering *CppRtf_List_Numbering::setSuffix(string suffix)
{
    m_suffix = suffix;
    return this;
}

CppRtf_List_Numbering *CppRtf_List_Numbering::setSeparator(string separator)
{
    m_separator = separator;
    return this;
}

string CppRtf_List_Numbering::getNumber(int number)
{
    switch ((NumberingTypes)m_type) {
        case TYPE_ALPHA_UPPER:
            return this->getAlphaNumber(number);
        case TYPE_ALPHA_LOWER:
            return this->getAlphaNumber(number, true);
        case TYPE_ROMAN_UPPER:
            return this->getRomanNumber(number);
        case TYPE_ROMAN_LOWER:
            return this->getRomanNumber(number, true);
        // default is alpha
        default:
            return cppstring::numtostr(number);
    }
}

string CppRtf_List_Numbering::getAlphaNumber(int number, bool lowerCase)
{
    using namespace phpstring;
    int asciiStartIndex = lowerCase ? 97 : 65;
    string alpha = "";
    while (number > 0) {
        int modulus = (number - 1) % 26;
        alpha += chr(modulus + asciiStartIndex);
        number = (int)((number - 1) / 26);
    }
    return strrev(alpha);
}

string CppRtf_List_Numbering::getRomanNumber(int number, bool lowerCase)
{
    string roman = "";

    vector<RomanChar> romanCharMapping;romanCharMapping.push_back(RomanChar("M",1000));
    romanCharMapping.push_back(RomanChar("CM",900));romanCharMapping.push_back(RomanChar("D",500));romanCharMapping.push_back(RomanChar("CD",400));
    romanCharMapping.push_back(RomanChar("C",100));romanCharMapping.push_back(RomanChar("XL",90));romanCharMapping.push_back(RomanChar("L",50));
    romanCharMapping.push_back(RomanChar("XL",40));romanCharMapping.push_back(RomanChar("X",10));romanCharMapping.push_back(RomanChar("IX",9));
    romanCharMapping.push_back(RomanChar("V",5));romanCharMapping.push_back(RomanChar("IV",4));romanCharMapping.push_back(RomanChar("I",1));

    for(vector<RomanChar>::iterator it = romanCharMapping.begin();it!=romanCharMapping.end();it++){
        RomanChar r = *it;
        string romanChar = r.symbol;
        int romanValue = r.number;

        // Determine the number of matches
        int matches = (int)(number / romanValue);

         // Store that many characters
        roman += phpstring::str_repeat(romanChar, matches);

        // Substract that from the number
        number = number % romanValue;

    }

    // The Roman numeral should be built, return it
    return lowerCase ? phpstring::strtolower(roman) : roman;
}

string CppRtf_List_Numbering::prefix()
{
    return m_prefix;
}

string CppRtf_List_Numbering::suffix()
{
    return m_suffix;
}

string CppRtf_List_Numbering::separator()
{
    return m_separator;
}

string CppRtf_List_Numbering::getListCharFontIndex()
{
    if (m_font) {
        string fontFamily = m_font->getFontFamily();
        int index = m_rtf->getFontTable()->getFontIndex(fontFamily);
        return cppstring::numtostr(index);
    }

    return CppRtf_List::getListCharFontIndex();
}

string CppRtf_List_Numbering::getListCharacter(int number)
{
    string listCharacter = m_prefix + this->getNumber(number) + m_suffix;
    return CppRtf::quoteRtfCode(listCharacter);
}
