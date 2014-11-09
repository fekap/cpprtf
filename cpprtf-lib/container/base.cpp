#include "base.h"
#include "element/plain.h"
#include "element/hyperlink.h"
#include "table.h"
#include "writer/interface.h"

CppRtf_Container_Base::CppRtf_Container_Base(CppRtf *rtf):
    m_pard("\\pard ")
{
    m_rtf=rtf;

//    __hash = BaseElement::_hash((unsigned char*)typeid(this).name()); //for instanceOf
    __name = typeid(this).name();
}

CppRtf *CppRtf_Container_Base::getRtf()
{
    return m_rtf;
}

int CppRtf_Container_Base::countElements()
{
    return m_elements.size();
}

vector<BaseElement*> CppRtf_Container_Base::getElements()
{
    return m_elements;
}

CppRtf_Element *CppRtf_Container_Base::writeRtfCode(string code, CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    CppRtf_Element* element = new CppRtf_Element(m_rtf,code, font, parFormat);
    element->setIsRtfCode();
    addElement(element);
    return element;
}

CppRtf_Element *CppRtf_Container_Base::writePlainRtfCode(string code)
{
    CppRtf_Element_Plain* element = new CppRtf_Element_Plain(m_rtf, code);
    element->setIsRtfCode();
    addElement(element);
    return element;
}

CppRtf_Element *CppRtf_Container_Base::addEmptyParagraph(CppRtf_Font *font, CppRtf_ParFormat *parFormat)
{
    if (parFormat == 0) {
        parFormat = new CppRtf_ParFormat();
    }
    CppRtf_Element* element = new CppRtf_Element(m_rtf, "\\par", font, parFormat);
    element->setIsRtfCode();
    addElement(element);
    return  element;
}

CppRtf_Element *CppRtf_Container_Base::writeText(string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat, bool convertTagsToRtf)
{
    CppRtf_Element* element = new CppRtf_Element(m_rtf, text, font, parFormat);
    if (convertTagsToRtf) {
        element->setConvertTagsToRtf();
    }
    addElement(element);
    return element;
}

CppRtf_Element *CppRtf_Container_Base::writeHyperLink(string hyperlink, string text, CppRtf_Font *font, CppRtf_ParFormat *parFormat, bool convertTagsToRtf)
{
    CppRtf_Element_Hyperlink* element = new CppRtf_Element_Hyperlink(m_rtf, text, font, parFormat);
    element->setHyperlink(hyperlink);
    if (convertTagsToRtf) {
        element->setConvertTagsToRtf();
    }
    addElement(element);
    return element;
}

CppRtf_Table *CppRtf_Container_Base::addTable(int alignment)
{
    CppRtf_Table* table = new CppRtf_Table(this, (CppRtf_Table::TableAligment)alignment);
    addElement(table);
    return table;
}

CppRtf_Image *CppRtf_Container_Base::addImage(string fileName, CppRtf_ParFormat *parFormat, float width, float height)
{
    CppRtf_Image* image = CppRtf_Image::createFromFile(m_rtf, fileName, width, height);
    if (parFormat) {
        image->setParFormat(parFormat);
    }
    addElement(image);
    return image;
}

CppRtf_Image *CppRtf_Container_Base::addImageFromString(string imageString, string type, CppRtf_ParFormat *parFormat, float width, float height)
{
    CppRtf_Image* image = CppRtf_Image::createFromString(m_rtf, imageString, type, width, height);
    if (parFormat) {
        image->setParFormat(parFormat);
    }
    addElement(image);
    return image;
}

void CppRtf_Container_Base::render()
{
    CppRtf_Writer_Interface* stream = m_rtf->getWriter();

    if (this->instanceOf<CppRtf_Table_Cell*>()&& this->countElements() == 0) {
        CppRtf_Table_Cell* cell = (CppRtf_Table_Cell *)this;
        stream->write("{");
        CppRtf_Font* font = this->getCellFont(this);
        if (font) {
            stream->write(font->getContent());
        }
        if ((!cell->isVerticalMerged() && !cell->isHorizontalMerged()) || cell->isVerticalMergedFirstInRange()) {
            stream->write("{\\~}");
        }
        stream->write("}\\intbl");
    }

    int lastKey = this->countElements() - 1;
    for(int key = 0; key<lastKey+1; key++){
        BaseElement *el = m_elements[key];
        if (this->instanceOf<CppRtf_Table_Cell*>()&& !(el->instanceOf<CppRtf_Table*>())){
            CppRtf_Table_Cell* cell = (CppRtf_Table_Cell *)this;
             // table cell initialization
            stream->write("\\intbl\\itap" + cppstring::numtostr(cell->getTable()->getNestDepth()) + "\r\n");
            stream->write(cell->getCellAlignment());
        }

        if (el->instanceOf<CppRtf_Element_Plain*>()) {
            CppRtf_Element_Plain* plain = (CppRtf_Element_Plain*)el->get();
            plain->render();
            continue;
        }

        CppRtf_ParFormat* parFormat = 0;

        if (!(el->instanceOf<CppRtf_Table*>())) {
            parFormat = el->getParFormat();
        }

        if (parFormat) {
            stream->write(m_pard);
            if (this->instanceOf<CppRtf_Table_Cell*>() && lastKey != key) {
                stream->write("{");
            }
            stream->write(parFormat->getContent());
        }

        CppRtf_Font* font = this->getCellFont(el);
        if (font) {
            stream->write(font->getContent());
        }

        el->render();

        if (this->needToAddParagraphEnd(key)) {
            stream->write("\\par ");
        }

        if (font) {
            stream->write(font->getClosingContent());
        }

        if (parFormat && this->instanceOf<CppRtf_Table_Cell*>() && lastKey != key) {
            stream->write("}");
        }
    }

}

bool CppRtf_Container_Base::needToAddParagraphEnd(int key)
{
    if ((int)m_elements.size()>key+1) {
        BaseElement *nextElement = m_elements[key + 1];
        BaseElement *elem = m_elements[key];
        bool isNextElementTable = nextElement->instanceOf<CppRtf_Table*>();


        //TODO
        bool instanceOfList = nextElement->instanceOf<CppRtf_List_Enumeration*>()||nextElement->instanceOf<CppRtf_List_Numbering*>()||nextElement->instanceOf<CppRtf_List*>();

        if (instanceOfList&& elem->instanceOf<CppRtf_Element*>()) {
            return true;
        }
        if (elem->instanceOf<CppRtf_Table*>() && ((CppRtf_Table*)elem->get())->getNestDepth() == 1) {
            return !((CppRtf_Table*)elem->get())->getPreventEmptyParagraph();
        }

        if (elem->instanceOf<CppRtf_Element*>()) {
            CppRtf_Element* e = (CppRtf_Element*)elem->get();
            return (!e->isEmptyParagraph() && (isNextElementTable || nextElement->getParFormat()));
        }
        if (elem->instanceOf<CppRtf_Image*>()) {
            return (isNextElementTable || nextElement->getParFormat());
        }
        if (instanceOfList) {
            return true;
        }
     }

    return false;
}

CppRtf_Font *CppRtf_Container_Base::getCellFont(BaseElement *elem)
{
    if (this->instanceOf<CppRtf_Table_Cell*>()&& !(elem->instanceOf<CppRtf_Table_Nested*>())){
        CppRtf_Table_Cell* cell = (CppRtf_Table_Cell *)this;
        return cell->getFont();
    }
    return (CppRtf_Font *)0;
}

CppRtf_Font *CppRtf_Container_Base::getCellFont(CppRtf_Container_Base *elem)
{
    if (this->instanceOf<CppRtf_Table_Cell*>()&& !(elem->instanceOf<CppRtf_Table_Nested*>())){
        CppRtf_Table_Cell* cell = (CppRtf_Table_Cell *)this;
        return cell->getFont();
    }
    return (CppRtf_Font *)0;
}
