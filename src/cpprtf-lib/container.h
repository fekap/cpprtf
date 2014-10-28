#ifndef CONTAINER_H
#define CONTAINER_H
#include "container/base.h"
#include "footnote.h"
#include "endnote.h"
#include "lists/enumeration.h"
#include "lists/numbering.h"
#include "formfield/checkbox.h"
#include "formfield/dropdown.h"
#include "formfield/text.h"

//Abstract class for creating containers like sections, footers and headers.
class CppRtf_Container : public CppRtf_Container_Base
{
public:
    CppRtf_Container(CppRtf* rtf);

    //adds a footnote
    CppRtf_Footnote* addFootnote(string noteText, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //adds an endnote
    CppRtf_Endnote* addEndnoot(string noteText, CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //adds list (enumeration/numbering)
    void addList(CppRtf_List* list);

    //adds enumeration
    void addEnumeration(CppRtf_List_Enumeration* enumeration);

    //adds enumeration
    void addNumbering(CppRtf_List_Numbering* numbering);

    //adds checkbox field
    CppRtf_FormField_Checkbox* addCheckbox(CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //adds dropdown field
    CppRtf_FormField_Dropdown* addDropdown(CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);

    //adds text field
    CppRtf_FormField_Text* addText(CppRtf_Font* font = 0, CppRtf_ParFormat* parFormat = 0);
};

#endif // CONTAINER_H
