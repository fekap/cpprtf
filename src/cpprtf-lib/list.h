#ifndef LIST_H
#define LIST_H
#include <vector>
#include <string>
#include "container/baseelement.h"
#include <iostream>

using namespace std;

class CppRtf;
class CppRtf_Font;
class CppRtf_ParFormat;
class CppRtf_Element;

//Abstract class for rtf lists (numberings and enumerations).
class CppRtf_List
{
public:
    CppRtf_List(CppRtf* rtf, int type = -1, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //adds item to list
    CppRtf_List* addItem(string text, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0, bool convertTagsToRtf = true);

    //adds element to list
    CppRtf_List* addElement(CppRtf_Element* element);

    //adds list to list
    CppRtf_List* addList(CppRtf_List* list);

    //sets list indent
    void setListIndent(float indent);

    //sets text indent
    void setTextIndent(float indent);

    //gets font
    CppRtf_Font* getFont();

    //gets par format
    CppRtf_ParFormat* getParFormat();

    //default implementation for getting font index for list character
    virtual string getListCharFontIndex(){
        return "";
    }

    //renders list
    void render();

    template<class type>
    bool instanceOf(){
        if(typeid(type).name()==__name){
            return true;
        }
        return false;
    }

protected:
    CppRtf* m_rtf;
    int m_type;//type of list
    CppRtf_Font* m_font;
    CppRtf_ParFormat*  m_parFormat;
    float m_listIndent; //indent to list character in centimeter
    float m_textIndent; //indent to text in centimeter
    vector<BaseElement*> m_items;

    template<class type>
    void addBaseElement(type newClass){
        BaseElement *e=new BaseElement();
        e->set(newClass);
        m_items.push_back(e);
    }


    //gets list character
    virtual string getListCharacter(int number) {
        (void)number;
        return "0";
    }

    const char* __name;

};

#endif // LIST_H
