#include "list.h"
#include "unit.h"
#include "element.h"
#include "lists/numbering.h"
#include "lists/enumeration.h"

CppRtf_List::CppRtf_List(CppRtf *rtf, int type, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    m_rtf = rtf;
    m_type = type;
    m_font = font;
    m_parFormat = parFormat;
    m_listIndent = CppRtf_Unit::UNIT_CM;
    m_textIndent = CppRtf_Unit::UNIT_CM;

    __name = typeid(this).name(); //for instanceOf;TODO

}

CppRtf_List *CppRtf_List::addItem(string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat, bool convertTagsToRtf)
{
    if (font == 0) {
        font = m_font;
    }
    if (parFormat == 0) {
        parFormat = m_parFormat;
    }

    CppRtf_Element* element = new CppRtf_Element(m_rtf, text, font, parFormat);
    if (convertTagsToRtf) {
        element->setConvertTagsToRtf();
    }
    addBaseElement(element);

    return this;
}

CppRtf_List *CppRtf_List::addElement(CppRtf_Element *element)
{
    addBaseElement(element);
    return this;
}

CppRtf_List *CppRtf_List::addList(CppRtf_List *list)
{
    if(list->instanceOf<CppRtf_List_Enumeration*>()){
        addBaseElement((CppRtf_List_Enumeration*)list);
    }
    if(list->instanceOf<CppRtf_List_Numbering*>()){
        addBaseElement((CppRtf_List_Numbering*)list);
    }
    if(list->instanceOf<CppRtf_List*>()){
        addBaseElement(list);
    }
    list->m_textIndent += m_textIndent;
    return this;
}

void CppRtf_List::setListIndent(float indent)
{
    m_listIndent = CppRtf_Unit::getUnitInTwips(indent);
}

void CppRtf_List::setTextIndent(float indent)
{
    m_textIndent = CppRtf_Unit::getUnitInTwips(indent);
}

CppRtf_Font *CppRtf_List::getFont()
{
    return m_font;
}

CppRtf_ParFormat *CppRtf_List::getParFormat()
{
    return m_parFormat;
}

void CppRtf_List::render()
{
    CppRtf_StreamOutput *stream = m_rtf->getWriter();
    int number = 0;

    for(vector<BaseElement*>::iterator it = m_items.begin();it!=m_items.end();it++ ) {
        BaseElement* item = *it;
        // item is a list
        if (item->instanceOf<CppRtf_List_Numbering*>() ) {
            if (this->instanceOf<CppRtf_List_Numbering*>()) {
                CppRtf_List_Numbering* numbering = (CppRtf_List_Numbering*)item;
                CppRtf_List_Numbering* numberingthis = (CppRtf_List_Numbering*)this;
                numbering->setPrefix(numberingthis->prefix() + numberingthis->getNumber(number) + numberingthis->separator());
                numbering->setSuffix(numberingthis->suffix());
            }
        }
        // item is a element
        else {
            number++;
            string listCharFontIndex  = this->getListCharFontIndex();
            string listCharacter      = this->getListCharacter(number);
            string listCharDefinition = "{\\*\\pn\\pnlvlblt\\pnf" + listCharFontIndex;
            if (m_font) {
                listCharDefinition += "\\pnfs" + cppstring::numtostr((m_font->getSize() * 2));
                string color = m_font->getColor();
                if (color.length()>0) {
                    int colorIndex = m_rtf->getColorTable()->getColorIndex(color);
                    listCharDefinition += "\\pncf" + cppstring::numtostr(colorIndex);
                }
            }
//            listCharDefinition += "bla";
//            listCharDefinition += "\\pnindent0{\\pntxtb " + listCharacter + "}}";

            float textIndent = m_listIndent + m_textIndent;

            stream->write("\\nowidctlpar\\fi-" + cppstring::numtostr(m_listIndent) + "\\li" + cppstring::numtostr(textIndent) + "\r\n");
            stream->write(listCharDefinition);
        }

        // renders item
        item->render();

        if (!item->instanceOf<CppRtf_List*>()) {
            stream->write("\\par\\pard\r\n");
        }
    }
}
