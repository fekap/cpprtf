#ifndef ENUMERATION_H
#define ENUMERATION_H
#include "list.h"

//Class for rtf enumerations.
class CppRtf_List_Enumeration : public CppRtf_List
{
public:

    //constants for enumeration types
    enum EnumerationTypes{
        TYPE_BULLET,
        TYPE_ARROW,
        TYPE_CIRCLE,
        TYPE_SQUARE,
        TYPE_DIAMOND
    };

    CppRtf_List_Enumeration(CppRtf* rtf, int type = -1, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

protected:
    CppRtf_Font* m_listCharFont;
    string m_listChar; //list charactor for the enumeration

    //inits list character definition
    void initListCharDefinition();

    //gets font index for list character
    string getListCharFontIndex();

    //gets list character
    string getListCharacter(int number);


};

#endif // ENUMERATION_H
