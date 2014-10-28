#include <CppRtf>
#include <container/section.h>
#include "lists/enumeration.h"

int main()
{
    CppRtf* rtf = new CppRtf();
    CppRtf_Container_Section* sect = rtf->addSection();

    sect->writeText("Text before the list");

    CppRtf_List_Enumeration *en = new CppRtf_List_Enumeration(rtf);
    en->addItem("hello world");
    en->addItem("foo");
    en->addItem("bar");
    CppRtf_List_Enumeration* subEnum = new CppRtf_List_Enumeration(rtf);
    subEnum->addItem("hello world");
    subEnum->addItem("foo");
    subEnum->addItem("bar");

    en->addList(subEnum);

    sect->addEnumeration(en);

    CppRtf_List_Numbering* subSubNumList = new CppRtf_List_Numbering(rtf);
    subSubNumList->addItem("hello world");
    subSubNumList->addItem("foo");
    subSubNumList->addItem("bar");

    CppRtf_List_Numbering* subNumList = new CppRtf_List_Numbering(rtf);
    subNumList->addItem("hello world");
    subNumList->addItem("foo");
    subNumList->addItem("bar");
    subNumList->addList(subSubNumList);

    CppRtf_Font* font = new CppRtf_Font(26, "Tahoma", "#f00");
    CppRtf_List_Numbering* numList = new CppRtf_List_Numbering(rtf, CppRtf_List_Numbering::TYPE_ALPHA_LOWER, font);
    numList->addItem("hello world");
    numList->addItem("foo");
    numList->addItem("bar");
    numList->addList(subNumList);
    numList->addItem("foobar");

//    sect->addNumbering(numList);

    // save rtf document
    rtf->save("lists.rtf");
    return 0;
}

