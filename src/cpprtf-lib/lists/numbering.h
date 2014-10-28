#ifndef NUMBERING_H
#define NUMBERING_H
#include "list.h"
#include "tools/stringtools.h"

//Class for rtf numberings.
class CppRtf_List_Numbering : public CppRtf_List
{
public:

    //constants for numbering types
    enum NumberingTypes{
        TYPE_ALPHA_UPPER,
        TYPE_ALPHA_LOWER,
        TYPE_ROMAN_UPPER,
        TYPE_ROMAN_LOWER
    };

    CppRtf_List_Numbering(CppRtf* rtf, int type = -1, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //sets prefix
    CppRtf_List_Numbering* setPrefix(string prefix);

    //sets suffix
    CppRtf_List_Numbering* setSuffix(string suffix);

    //sets separator
    CppRtf_List_Numbering* setSeparator(string separator);

    //gets number
    string getNumber(int number);

    //getters
    string prefix();
    string suffix();
    string separator();

protected:

    string m_prefix;
    string m_suffix;
    string m_separator;

    //gets font index for list character
    string getListCharFontIndex();

    //gets list character
    string getListCharacter(int number);


private:

    class RomanChar{
    public:
        string symbol;
        int number;
        RomanChar(string sym,int num){
            symbol = sym;
            number = num;
        }
    };

    //gets alpha number
    string getAlphaNumber(int number, bool lowerCase = false);

    //gets roman number; Code based from: http://www.sajithmr.me/php-decimal-to-roman-number-conversion/
    string getRomanNumber(int number, bool lowerCase = false);

};

#endif // NUMBERING_H
