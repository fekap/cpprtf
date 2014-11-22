#include "baseelement.h"
#include "element.h"
#include "table/cell.h"
#include "table/nested.h"
#include "table.h"
#include "footnote.h"
#include "formfield.h"
#include "image.h"
#include "list.h"
#include "container/section.h"

BaseElement::BaseElement()
{
    m_pointer = 0;
}

BaseElement::~BaseElement()
{
    smartPointer(m_pointer);
}

CppRtf_ParFormat *BaseElement::getParFormat()
{
    if(instanceOf<CppRtf_Element*>()){
        CppRtf_Element* element = (CppRtf_Element*)get();
        return element->getParFormat();
    }
    if(instanceOf<CppRtf_Footnote*>()){
        CppRtf_Footnote* element = (CppRtf_Footnote*)get();
        return element->getParFormat();
    }
    if(instanceOf<CppRtf_FormField*>()){
        CppRtf_FormField* element = (CppRtf_FormField*)get();
        return element->getParFormat();
    }
    if(instanceOf<CppRtf_Image*>()){
        CppRtf_Image* element = (CppRtf_Image*)get();
        return element->getParFormat();
    }
    if(instanceOf<CppRtf_List*>()){
        CppRtf_List* element = (CppRtf_List*)get();
        return element->getParFormat();
    }
}

void BaseElement::render()
{
    if(instanceOf<CppRtf_Element*>()){
        CppRtf_Element* element = (CppRtf_Element*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Table*>()){
        CppRtf_Table* element = (CppRtf_Table*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Table_Cell*>()){
        CppRtf_Table_Cell* element = (CppRtf_Table_Cell*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Table_Nested*>()){
        CppRtf_Table_Nested* element = (CppRtf_Table_Nested*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Container_Base*>()){
        CppRtf_Container_Base* element = (CppRtf_Container_Base*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Container_Section*>()){
        CppRtf_Container_Section* element = (CppRtf_Container_Section*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Container_Header*>()){
        CppRtf_Container_Header* element = (CppRtf_Container_Header*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Container_Section*>()){
        CppRtf_Container_Section* element = (CppRtf_Container_Section*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Footnote*>()){
        CppRtf_Footnote* element = (CppRtf_Footnote*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Endnote*>()){
        CppRtf_Endnote* element = (CppRtf_Endnote*)get(); //TODO
        element->render();
    }
    if(instanceOf<CppRtf_FormField_Checkbox*>()){
        CppRtf_FormField_Checkbox* element = (CppRtf_FormField_Checkbox*)get();
        element->render();
    }

    if(instanceOf<CppRtf_FormField_Dropdown*>()){
        CppRtf_FormField_Dropdown* element = (CppRtf_FormField_Dropdown*)get();
        element->render();
    }

    if(instanceOf<CppRtf_FormField_Text*>()){
        CppRtf_FormField_Text* element = (CppRtf_FormField_Text*)get();
        element->render();
    }

    if(instanceOf<CppRtf_List*>()){
        CppRtf_List* element = (CppRtf_List*)get();
        element->render();
    }
    if(instanceOf<CppRtf_List_Enumeration*>()){
        CppRtf_List_Enumeration* element = (CppRtf_List_Enumeration*)get();
        element->render();
    }
    if(instanceOf<CppRtf_List_Numbering*>()){
        CppRtf_List_Numbering* element = (CppRtf_List_Numbering*)get();
        element->render();
    }
    if(instanceOf<CppRtf_Image*>()){
        CppRtf_Image* element = (CppRtf_Image*)get();
        element->render();
    }
    //TODO остальные классы (Image)
}
